//

// File:       hello.c

//

// Abstract:   A simple "Hello World" compute example showing basic usage of OpenCL which

//             calculates the mathematical square (X[i] = pow(X[i],2)) for a buffer of

//             floating point values.

//             

//

// Version:    <1.0>

//

// Disclaimer: IMPORTANT:  This Apple software is supplied to you by Apple Inc. ("Apple")

//             in consideration of your agreement to the following terms, and your use,

//             installation, modification or redistribution of this Apple software

//             constitutes acceptance of these terms.  If you do not agree with these

//             terms, please do not use, install, modify or redistribute this Apple

//             software.

//

//             In consideration of your agreement to abide by the following terms, and

//             subject to these terms, Apple grants you a personal, non - exclusive

//             license, under Apple's copyrights in this original Apple software ( the

//             "Apple Software" ), to use, reproduce, modify and redistribute the Apple

//             Software, with or without modifications, in source and / or binary forms;

//             provided that if you redistribute the Apple Software in its entirety and

//             without modifications, you must retain this notice and the following text

//             and disclaimers in all such redistributions of the Apple Software. Neither

//             the name, trademarks, service marks or logos of Apple Inc. may be used to

//             endorse or promote products derived from the Apple Software without specific

//             prior written permission from Apple.  Except as expressly stated in this

//             notice, no other rights or licenses, express or implied, are granted by

//             Apple herein, including but not limited to any patent rights that may be

//             infringed by your derivative works or by other works in which the Apple

//             Software may be incorporated.

//

//             The Apple Software is provided by Apple on an "AS IS" basis.  APPLE MAKES NO

//             WARRANTIES, EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION THE IMPLIED

//             WARRANTIES OF NON - INFRINGEMENT, MERCHANTABILITY AND FITNESS FOR A

//             PARTICULAR PURPOSE, REGARDING THE APPLE SOFTWARE OR ITS USE AND OPERATION

//             ALONE OR IN COMBINATION WITH YOUR PRODUCTS.

//

//             IN NO EVENT SHALL APPLE BE LIABLE FOR ANY SPECIAL, INDIRECT, INCIDENTAL OR

//             CONSEQUENTIAL DAMAGES ( INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF

//             SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS

//             INTERRUPTION ) ARISING IN ANY WAY OUT OF THE USE, REPRODUCTION, MODIFICATION

//             AND / OR DISTRIBUTION OF THE APPLE SOFTWARE, HOWEVER CAUSED AND WHETHER

//             UNDER THEORY OF CONTRACT, TORT ( INCLUDING NEGLIGENCE ), STRICT LIABILITY OR

//             OTHERWISE, EVEN IF APPLE HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

//

// Copyright ( C ) 2008 Apple Inc. All Rights Reserved.

//

 

////////////////////////////////////////////////////////////////////////////////

 

#include <fcntl.h>

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <math.h>

#include <unistd.h>

#include <sys/types.h>

#include <sys/stat.h>

#include <OpenCL/opencl.h>

 

////////////////////////////////////////////////////////////////////////////////

 

// Use a static data size for simplicity

//

#define DATA_SIZE (65536)

 

////////////////////////////////////////////////////////////////////////////////

 

// Simple compute kernel which computes the square of an input array 

//

const char *KernelSource = "\n" \

"__kernel void square(                                                       \n" \

"   __global float* input,                                              \n" \

"   __global float* output,                                             \n" \

"   const unsigned int count)                                           \n" \

"{                                                                      \n" \

"   int i = get_global_id(0);                                           \n" \

"   if(i < count)                                                       \n" \

"       output[i] = input[i] * input[i];                                \n" \

"}                                                                      \n" \

"\n";

 

////////////////////////////////////////////////////////////////////////////////

 

int main(int argc, char** argv)

{

    int err;                            // error code returned from api calls

      

    float data[DATA_SIZE];              // original data set given to device

    float results[DATA_SIZE];           // results returned from device

    unsigned int correct;               // number of correct results returned

 

    size_t global;                      // global domain size for our calculation

    size_t local;                       // local domain size for our calculation

 

    cl_device_id device_id;             // compute device id 

    cl_context context;                 // compute context

    cl_command_queue commands;          // compute command queue

    cl_program program;                 // compute program

    cl_kernel kernel;                   // compute kernel

    

    cl_mem input;                       // device memory used for the input array

    cl_mem output;                      // device memory used for the output array

    

    // Fill our data set with random float values

    //

    int i = 0;

    unsigned int count = DATA_SIZE;

    for(i = 0; i < count; i++)

        data[i] = rand() / (float)RAND_MAX;

    

    // Connect to a compute device

    //

    int gpu = 1;

	/*cl_int clGetDeviceIDs(cl_platform_id platform, cl_device_type device_type, cl_uint num_entries, cl_device_id *devices,cl_uint *num_devices)*/
	err = clGetDeviceIDs(NULL, gpu ? CL_DEVICE_TYPE_GPU : CL_DEVICE_TYPE_CPU, 1, &device_id, NULL);

    if (err != CL_SUCCESS)

    {

        printf("Error: Failed to create a device group!\n");

        return EXIT_FAILURE;

    }

  

    // Create a compute context 

    //
	//https://www.khronos.org/registry/cl/sdk/1.2/docs/man/xhtml/clCreateContext.html
	//cl_context clCreateContext(const cl_context_properties *properties, cl_uint num_devices, const cl_device_id *devices, (void CL_CALLBACK  *pfn_notify)(const char *errinfo,const void *private_info, size_t cb,void *user_data), void *user_data, cl_int *errcode_ret);
    context = clCreateContext(0, 1, &device_id, NULL, NULL, &err);

    if (!context)

    {

        printf("Error: Failed to create a compute context!\n");

        return EXIT_FAILURE;

    }


 

    // Create the compute program from the source buffer

    //http://www.khronos.org/registry/cl/sdk/1.2/docs/man/xhtml/clCreateProgramWithSource.html
	//cl_program clCreateProgramWithSource(cl_context context, cl_uint count, const char **strings, const size_t *lengths, cl_int *errcode_ret)

    program = clCreateProgramWithSource(context, 1, (const char **) & KernelSource, NULL, &err);

    if (!program)

    {

        printf("Error: Failed to create compute program!\n");

        return EXIT_FAILURE;

    }

 

    // Build the program executable

    //https://www.khronos.org/registry/cl/sdk/1.2/docs/man/xhtml/clBuildProgram.html
	//cl_int clBuildProgram(cl_program program, cl_uint num_devices, const cl_device_id *device_list, const char *options, void (CL_CALLBACK *pfn_notify)(cl_program program, void *user_data),void *user_data)
    err = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);

    if (err != CL_SUCCESS)

    {

        size_t len;

        char buffer[2048];

 

        printf("Error: Failed to build program executable!\n");

        clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, &len);

        printf("%s\n", buffer);

        exit(1);

    }

 

    // Create the compute kernel in the program we wish to run

    //https://www.khronos.org/registry/cl/sdk/2.0/docs/man/xhtml/clCreateKernel.html
	//cl_kernel clCreateKernel(cl_program  program, const char *kernel_name, cl_int *errcode_ret)

    kernel = clCreateKernel(program, "square", &err);

    if (!kernel || err != CL_SUCCESS)

    {

        printf("Error: Failed to create compute kernel!\n");

        exit(1);

    }

 

    // Create the input and output arrays in device memory for our calculation

	//https://www.khronos.org/registry/cl/sdk/1.2/docs/man/xhtml/clCreateBuffer.html
	//l_mem clCreateBuffer(cl_context context, cl_mem_flags flags, size_t size, void *host_ptr, cl_int *errcode_ret);

    input = clCreateBuffer(context,  CL_MEM_READ_ONLY,  sizeof(float) * count, NULL, NULL);

    output = clCreateBuffer(context, CL_MEM_WRITE_ONLY, sizeof(float) * count, NULL, NULL);

    if (!input || !output)

    {

        printf("Error: Failed to allocate device memory!\n");

        exit(1);

    }    

    // Create a command commands

	//https://www.khronos.org/registry/cl/sdk/1.0/docs/man/xhtml/clCreateCommandQueue.html<Paste>
	//cl_command_queue clCreateCommandQueue(cl_context context, cl_device_id device, cl_command_queue_properties properties, cl_int *errcode_ret);
	commands = clCreateCommandQueue(context, device_id, 0, &err);

    if (!commands)

    {

        printf("Error: Failed to create a command commands!\n");

        return EXIT_FAILURE;

    }

    // Write our data set into the input array in device memory 

    //https://www.khronos.org/registry/cl/sdk/1.2/docs/man/xhtml/clEnqueueWriteBuffer.html
	//cl_int clEnqueueWriteBuffer(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_write, size_t offset, size_t size, const void *ptr, cl_uint num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event)
    err = clEnqueueWriteBuffer(commands, input, CL_TRUE, 0, sizeof(float) * count, data, 0, NULL, NULL);

    if (err != CL_SUCCESS)

    {

        printf("Error: Failed to write to source array!\n");

        exit(1);

    }

 

    // Set the arguments to our compute kernel

    //https://www.khronos.org/registry/cl/sdk/1.1/docs/man/xhtml/clSetKernelArg.html
	//cl_int clSetKernelArg(cl_kernel kernel, cl_uint arg_index, size_t arg_size, const void *arg_value)
    err = 0;

    err  = clSetKernelArg(kernel, 0, sizeof(cl_mem), &input);

    err |= clSetKernelArg(kernel, 1, sizeof(cl_mem), &output);

    err |= clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);

    if (err != CL_SUCCESS)

    {

        printf("Error: Failed to set kernel arguments! %d\n", err);

        exit(1);

    }

 

    // Get the maximum work group size for executing the kernel on the device

    //https://www.khronos.org/registry/cl/sdk/1.2/docs/man/xhtml/clGetKernelWorkGroupInfo.html
	//cl_int clGetKernelWorkGroupInfo(cl_kernel  kernel, cl_device_id  device, cl_kernel_work_group_info  param_name, size_t  param_value_size, void  *param_value, size_t  *param_value_size_ret)

    err = clGetKernelWorkGroupInfo(kernel, device_id, CL_KERNEL_WORK_GROUP_SIZE, sizeof(local), &local, NULL);

    if (err != CL_SUCCESS)

    {

        printf("Error: Failed to retrieve kernel work group info! %d\n", err);

        exit(1);

    }

 

    // Execute the kernel over the entire range of our 1d input data set

    // using the maximum number of work group items for this device

    //https://www.khronos.org/registry/cl/sdk/1.2/docs/man/xhtml/clEnqueueNDRangeKernel.html
	//cl_int clEnqueueNDRangeKernel(cl_command_queue command_queue, cl_kernel kernel, cl_uint work_dim, const size_t *global_work_offset, const size_t *global_work_size,
	//const size_t *local_work_size, cl_uint num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event) 

    global = count;

    err = clEnqueueNDRangeKernel(commands, kernel, 1, NULL, &global, &local, 0, NULL, NULL);

    if (err)

    {

        printf("Error: Failed to execute kernel!\n");

        return EXIT_FAILURE;

    }

 

    // Wait for the command commands to get serviced before reading back results

    //

    clFinish(commands);

 

    // Read back the results from the device to verify the output

    //

    err = clEnqueueReadBuffer( commands, output, CL_TRUE, 0, sizeof(float) * count, results, 0, NULL, NULL );  

    if (err != CL_SUCCESS)

    {

        printf("Error: Failed to read output array! %d\n", err);

        exit(1);

    }

    

    // Validate our results

    //

    correct = 0;

    for(i = 0; i < count; i++)

    {

        if(results[i] == data[i] * data[i])

            correct++;

    }

    

    // Print a brief summary detailing the results

    //

    printf("Computed '%d/%d' correct values!\n", correct, count);

    

    // Shutdown and cleanup

    //

    clReleaseMemObject(input);

    clReleaseMemObject(output);

    clReleaseProgram(program);

    clReleaseKernel(kernel);

    clReleaseCommandQueue(commands);

    clReleaseContext(context);

 

    return 0;

}
