__kernel void primos(__global int *vet_primos) {
    
    // Get the index of the current element
    int num = get_global_id(0);
    int i = 0;
    int flag = 0;

    for(i=2; i<num; i++)
    {
    	if(num%i == 0)
    	{
    		flag =1;
    		break;
    	}
    }
    if(flag == 0)
    {
    	vet_primos[num]++;
    }

    // Do the operation
    //C[i] = A[i] + B[i];

}
