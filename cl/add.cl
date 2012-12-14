__kernel void vector_add(__global const float4 *A, __global const float4 *B, __global float4 *C) {
 
    // Get the index of the current element to be processed
    int i = get_global_id(0);
 
    // Do the operation
    C[i] = A[i] + B[i];
}