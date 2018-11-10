//------------------------------------------------------------------------------
//
// Name:       solution.c
//
// Purpose:    Mine solution for the problem
//             C = A + B
//             D = C + E
//             F + D + G
//
//
// HISTORY:    Based on the vadd_c.c
//------------------------------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/types.h>
#ifdef __APPLE__
#define RICH_BOY
#include <OpenCL/opencl.h>
#include <unistd.h>
#else
#include <CL/cl.h>
#endif

#include "err_code.h"

//pick up device type from compiler command line or from
//the default type
#ifndef DEVICE
#define DEVICE CL_DEVICE_TYPE_DEFAULT
#endif
#define CL_USE_DEPRECATED_OPENCL_1_2_APIS


extern double wtime();       // returns time since some fixed past point (wtime.c)
extern int output_device_info(cl_device_id );


//------------------------------------------------------------------------------

#define TOL    (0.001)   // tolerance used in floating point comparisons
#define LENGTH (1024)    // length of the arrays

//------------------------------------------------------------------------------
//
// kernel:  vadd
//
// Purpose: Compute the elementwise sum c = a+b
//
// input: a and b float vectors of length count
//
// output: c float vector of length count holding the sum a + b
//

const char *KernelSource = "\n" \
                            "__kernel void vadd(                                                 \n" \
                            "   __global float* a,                                                  \n" \
                            "   __global float* b,                                                  \n" \
                            "   __global float* c,                                                  \n" \
                            "   const unsigned int count)                                           \n" \
                            "{                                                                      \n" \
                            "   int i = get_global_id(0);                                           \n" \
                            "   if(i < count)                                                       \n" \
                            "       c[i] = a[i] + b[i];                                             \n" \
                            "   else                                                                \n" \
                            "       c[0] = 999;                                                     \n" \
                            "}                                                                      \n" \
                            "\n";

//------------------------------------------------------------------------------


int main(int argc, char** argv)
{
  argc = argc;
  argv = argv;
  // INITIALIZATION
  // =========================================
  int          err;               // error code returned from OpenCL calls

  float*       h_a = (float*) calloc(LENGTH, sizeof(float));       // a vector
  assert(h_a);
  float*       h_b = (float*) calloc(LENGTH, sizeof(float));       // b vector
  assert(h_b);
  float*       h_c = (float*) calloc(LENGTH, sizeof(float));       // c vector
  assert(h_c);
  float*       h_d = (float*) calloc(LENGTH, sizeof(float));       // d vector
  assert(h_d);
  float*       h_e = (float*) calloc(LENGTH, sizeof(float));       // e vector
  assert(h_e);
  float*       h_f = (float*) calloc(LENGTH, sizeof(float));       // f vector
  assert(h_f);
  float*       h_g = (float*) calloc(LENGTH, sizeof(float));       // g vector
  assert(h_g);

  unsigned int correct;           // number of correct results

  cl_device_id     device_id;     // compute device id
  cl_context       context;       // compute context
  cl_command_queue commands;      // compute command queue
  cl_program       program;       // compute program
  cl_kernel        ko_vadd;       // compute kernel

  cl_mem d_a;                     // device memory used for the input  a vector
  cl_mem d_b;                     // device memory used for the input  b vector
  cl_mem d_c;                     // device memory used for the output c vector
  cl_mem d_d;                     // device memory used for the output d vector
  cl_mem d_e;                     // device memory used for the output e vector
  cl_mem d_f;                     // device memory used for the output f vector
  cl_mem d_g;                     // device memory used for the output g vector

  // Fill input vectors with random floats
  int count = LENGTH;
  for(int i = 0; i < count; i++){
    h_a[i] = rand() / (float)RAND_MAX;
    h_b[i] = rand() / (float)RAND_MAX;
    h_e[i] = rand() / (float)RAND_MAX;
    h_g[i] = rand() / (float)RAND_MAX;
  }

  // Set up platform and GPU device
  // =========================================

  cl_uint numPlatforms;
  // Find number of platforms
  err = clGetPlatformIDs(0, NULL, &numPlatforms);
  checkError(err, "Finding platforms");
  if (numPlatforms == 0)
  {
    printf("Found 0 platforms!\n");
    return EXIT_FAILURE;
  }

  // Get all platforms
  cl_platform_id *Platform = (cl_platform_id *)calloc(numPlatforms, sizeof(cl_platform_id));
  assert(Platform);
  err = clGetPlatformIDs(numPlatforms, Platform, NULL);
  checkError(err, "Getting platforms");

  // Secure a GPU
  for (unsigned i = 0; i < numPlatforms; i++)
  {
    err = clGetDeviceIDs(Platform[i], DEVICE, 1, &device_id, NULL);
    if (err == CL_SUCCESS)
      break;
  }

  if (device_id == NULL)
    checkError(err, "Finding a device");

  //err = output_device_info(device_id); // TODO remove
  //checkError(err, "Printing device output");

  // Create a compute context
  context = clCreateContext(0, 1, &device_id, NULL, NULL, &err);
  checkError(err, "Creating context");

  // Create a command queue
//  commands = clCreateCommandQueue(context, device_id, 0, &err);
  commands = clCreateCommandQueueWithProperties(context, device_id, 0, &err);
  checkError(err, "Creating command queue");

  // Create the compute program from the source buffer
  program = clCreateProgramWithSource(context, 1, (const char **) & KernelSource, NULL, &err);
  checkError(err, "Creating program");

  // Build the program
  err = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
  if (err != CL_SUCCESS)
  {
    size_t len;
    char buffer[2048];

    printf("Error: Failed to build program executable!\n%s\n", err_code(err));
    clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, &len);
    printf("%s\n", buffer);
    return EXIT_FAILURE;
  }

  // Create the compute kernel from the program
  ko_vadd = clCreateKernel(program, "vadd", &err);
  checkError(err, "Creating kernel");

  d_a = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(float) * count, h_a, &err);
  checkError(err, "Creating buffer d_a");
  d_b = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(float) * count, h_b, &err);
  checkError(err, "Creating buffer d_b");
  d_e  = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(float) * count, h_e, &err);
  checkError(err, "Creating buffer d_e");
  d_g  = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(float) * count, h_g, &err);
  checkError(err, "Creating buffer d_g");

  d_c  = clCreateBuffer(context,  CL_MEM_READ_WRITE, sizeof(float) * count, NULL, &err);
  checkError(err, "Creating buffer d_c");
  d_d  = clCreateBuffer(context,  CL_MEM_READ_WRITE, sizeof(float) * count, NULL, &err);
  checkError(err, "Creating buffer d_d");

  d_f  = clCreateBuffer(context,  CL_MEM_WRITE_ONLY, sizeof(float) * count, NULL, &err);
  checkError(err, "Creating buffer d_f");

  // executing C = A + B
  err  = clSetKernelArg(ko_vadd, 0, sizeof(cl_mem), &d_a);
  err |= clSetKernelArg(ko_vadd, 1, sizeof(cl_mem), &d_b);
  err |= clSetKernelArg(ko_vadd, 2, sizeof(cl_mem), &d_c);
  err |= clSetKernelArg(ko_vadd, 3, sizeof(unsigned int), &count);
  checkError(err, "Setting kernel arguments, part 1");

  err = clEnqueueNDRangeKernel(commands, ko_vadd, 1, NULL, (size_t *)(&count), NULL, 0, NULL, NULL);
  checkError(err, "Enqueueing kernel, part 1");

  // executing D = C + E
  err = clSetKernelArg(ko_vadd, 0, sizeof(cl_mem), &d_c);
  err |= clSetKernelArg(ko_vadd, 1, sizeof(cl_mem), &d_e);
  err |= clSetKernelArg(ko_vadd, 2, sizeof(cl_mem), &d_d);
  checkError(err, "Setting kernel arguments, part 2");

  err = clEnqueueNDRangeKernel(commands, ko_vadd, 1, NULL, (size_t *)(&count), NULL, 0, NULL, NULL);
  checkError(err, "Enqueueing kernel, part 2");

  // executing F = D + G
  err = clSetKernelArg(ko_vadd, 0, sizeof(cl_mem), &d_d);
  err |= clSetKernelArg(ko_vadd, 1, sizeof(cl_mem), &d_g);
  err |= clSetKernelArg(ko_vadd, 2, sizeof(cl_mem), &d_f);
  checkError(err, "Setting kernel arguments, part 3");

  err = clEnqueueNDRangeKernel(commands, ko_vadd, 1, NULL, (size_t *)(&count), NULL, 0, NULL, NULL);
  checkError(err, "Enqueueing kernel, part 3");

  // Wait for the commands to complete before stopping the timer
  err = clFinish(commands);
  checkError(err, "Waiting for kernel to finish");

  double rtime = wtime();

  rtime = wtime() - rtime;
  printf("\nThe kernel ran in %lf seconds\n",rtime);

  // Read back the results from the compute device
  err = clEnqueueReadBuffer( commands, d_c, CL_TRUE, 0, sizeof(float) * count, h_c, 0, NULL, NULL );
  err |= clEnqueueReadBuffer( commands, d_d, CL_TRUE, 0, sizeof(float) * count, h_d, 0, NULL, NULL);
  err |= clEnqueueReadBuffer( commands, d_f, CL_TRUE, 0, sizeof(float) * count, h_f, 0, NULL, NULL);
  if (err != CL_SUCCESS)
  {
    printf("Error: Failed to read output arrays!\n%s\n", err_code(err));
    exit(1);
  }

  // Test the results
  correct = 0;
  float tmp;

  for(int i = 0; i < count; i++)
  {
    tmp = h_a[i] + h_b[i];     // assign element i of a+b to tmp
    tmp -= h_c[i];             // compute deviation of expected and output result
    if(tmp*tmp < TOL*TOL)        // correct if square deviation is less than tolerance squared
      correct++;
    else
      printf(" tmp %f h_a %f h_b %f h_c %f \n",tmp, h_a[i], h_b[i], h_c[i]);
    tmp = h_c[i] + h_e[i];
    tmp -= h_d[i];
    if(tmp*tmp < TOL*TOL)        // correct if square deviation is less than tolerance squared
      correct++;
    else
      printf(" tmp %f h_c %f h_e %f h_d %f \n",tmp, h_c[i], h_e[i], h_d[i]);
    tmp = h_d[i] + h_g[i];
    tmp -= h_f[i];
    if(tmp*tmp < TOL*TOL)        // correct if square deviation is less than tolerance squared
      correct++;
    else
      printf(" tmp %f h_d %f h_g %f h_f %f \n",tmp, h_d[i], h_g[i], h_f[i]);
  }

  // summarise results
  printf("C = A+B, D = C+E, F = D+G:  %d out of %d results were correct.\n", correct, count*3);

  // cleanup then shutdown
  clReleaseMemObject(d_a);
  clReleaseMemObject(d_b);
  clReleaseMemObject(d_c);
  clReleaseMemObject(d_d);
  clReleaseMemObject(d_e);
  clReleaseMemObject(d_f);
  clReleaseMemObject(d_g);
  clReleaseProgram(program);
  clReleaseKernel(ko_vadd);
  clReleaseCommandQueue(commands);
  clReleaseContext(context);

  free(h_a);
  free(h_b);
  free(h_c);
  free(h_d);
  free(h_e);
  free(h_f);
  free(h_g);

  return 0;
}

