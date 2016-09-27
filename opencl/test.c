/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguarda <lguarda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 15:43:35 by lguarda           #+#    #+#             */
/*   Updated: 2016/09/27 18:49:54 by lguarda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>                                                                                                                                               
#include <stdlib.h>
#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif
 
int main() {
 
    int i, j;
    char* value;
    size_t valueSize;
    cl_uint cf;
    cl_uint platformCount;
    cl_platform_id* platforms;
    cl_uint deviceCount;
    cl_device_id* devices;
    cl_uint maxComputeUnits;
 
    // get all platforms
    clGetPlatformIDs(0, NULL, &platformCount);
    platforms = (cl_platform_id*) malloc(sizeof(cl_platform_id) * platformCount);
    clGetPlatformIDs(platformCount, platforms, NULL);
 
    for (i = 0; i < platformCount; i++) {
 
        // get all devices
        clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, 0, NULL, &deviceCount);
        devices = (cl_device_id*) malloc(sizeof(cl_device_id) * deviceCount);
        clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, deviceCount, devices, NULL);
 
		clGetPlatformInfo(platforms[i], CL_PLATFORM_NAME, 0, NULL, &valueSize);
		value = (char*) malloc(valueSize);
		clGetPlatformInfo(platforms[i], CL_PLATFORM_NAME, valueSize, value, NULL);
		printf("_ Platform Name: %s\n", value);
		free(value);
        // for each device print critical attributes
        for (j = 0; j < deviceCount; j++) {
 
            // print device name
            clGetDeviceInfo(devices[j], CL_DEVICE_NAME, 0, NULL, &valueSize);
            value = (char*) malloc(valueSize);
            clGetDeviceInfo(devices[j], CL_DEVICE_NAME, valueSize, value, NULL);
            printf("%d. Device: %s\n", j+1, value);
            free(value);
 
            // print hardware device version
            clGetDeviceInfo(devices[j], CL_DEVICE_VERSION, 0, NULL, &valueSize);
            value = (char*) malloc(valueSize);
            clGetDeviceInfo(devices[j], CL_DEVICE_VERSION, valueSize, value, NULL);
            printf(" %d.%d Hardware version: %s\n", j+1, 1, value);
            free(value);
 
            // print software driver version
            clGetDeviceInfo(devices[j], CL_DRIVER_VERSION, 0, NULL, &valueSize);
            value = (char*) malloc(valueSize);
            clGetDeviceInfo(devices[j], CL_DRIVER_VERSION, valueSize, value, NULL);
            printf(" %d.%d Software version: %s\n", j+1, 2, value);
            free(value);
 
            // print c version supported by compiler for device
            clGetDeviceInfo(devices[j], CL_DEVICE_OPENCL_C_VERSION, 0, NULL, &valueSize);
            value = (char*) malloc(valueSize);
            clGetDeviceInfo(devices[j], CL_DEVICE_OPENCL_C_VERSION, valueSize, value, NULL);
            printf(" %d.%d OpenCL C version: %s\n", j+1, 3, value);
            free(value);

            clGetDeviceInfo(devices[j], CL_DEVICE_MAX_CLOCK_FREQUENCY, sizeof(cl_uint), &cf, NULL);
            printf(" %d.%d Maximum configured clock frequency: %U MHz\n", j+1, 4, cf);

            clGetDeviceInfo(devices[j], CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, sizeof(cl_uint), &cf, NULL);
            printf(" %d.%d Maximum work item dimensions: %U\n", j+1, 5, cf);

            clGetDeviceInfo(devices[j], CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(cl_uint), &cf, NULL);
            printf(" %d.%d Maximum work group size: %U\n", j+1, 6, cf);

            // print parallel compute units
            clGetDeviceInfo(devices[j], CL_DEVICE_MAX_COMPUTE_UNITS,
                    sizeof(maxComputeUnits), &maxComputeUnits, NULL);
            printf(" %d.%d Parallel compute units: %d\n\n", j+1, 7, maxComputeUnits);
 
        }
 
        free(devices);
 
    }
 
    free(platforms);
    return 0;
 
}
