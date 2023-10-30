# GLM-AGV
# Act as an agent for multiple AGVs in flexible workshops and schedule AGVs through large models (GLM)
Implement scheduling through large models, minimize problems, and achieve multi-AGV scheduling results. Accelerate scheduling results through fine-tuning of large models.
The data stored each time must be managed centrally.
Flexible production: A flexible job shop has multiple workpieces N, and each workpiece has its own set of processes. The processing procedures cannot be disrupted, and each procedure can only be processed on one machine. Processing cannot be paused. There may be multiple machines that can process a workpiece, and the processing times are different.
AGV: AGV serves as transportation task in flexible production. Each AGV can only transport one workpiece in the workshop. The currently transported workpiece will be unbound only after all processes are completed. The AGV returns to the initial position to transport the next workpiece. The AGV reaches the target location where the machine is located. It will wait at the machine's target location for the current transport workpiece process to complete processing and transport it to the next location. What needs to be noted is that multiple AGVs cannot share a location point, which means that multiple AGVs cannot share a location at the same time during transportation. When an AGV stops at the machine. Other AGVs cannot be at the current machine location. Need to stop at a point adjacent to the machine.
The AGV dispatcher controls the direction and speed of three AGVs, allowing them to move within a workshop to execute the scheduling results you output.

In order to set the AGV's initial position to reach the target machine point. You work as a dispatcher. The direction and speed of the AGV can only be controlled within 1 second. (That is, move one space)

AGV has 4 directions: {1 2 3 4} 1 means up, 2 means down, 3 means left, 4 right. The speed bits of AGV: {0, 1} 0 means stop and 1 means move forward.

Every second after the operation is completed, I will return the current AGV position information, the completion time of the workpiece process, and its own task set (sequential relationship). The position and current status of the machine (whether it is occupied), the current position, speed, direction of the agv, the current process of transporting the workpiece, whether it has reached the machine selected for the processing process, if it is large, the status value is 1, stay at the current position and start processing , there is very little time left
```
##################################
#**1*****************************#
#**************m*****************#
#********************************#
#********************************#
#*************m******************#
#**2*****************************#
#********************************#
#*************m******************#
#**3*****************************#
#************m*******************#
#********************************#
##################################

```

Initial workshop information: It is represented by # and * and numbers. # represents the bit wall * represents the path. The numbers {1,2,3} represent AGV. An array represents the workshop location information. You may use the workshop layout in subsequent judgments
