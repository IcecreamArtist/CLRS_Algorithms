# assignment one
2019051625 党禧琳

![img_12.png](img_12.png)

The I/O device is idle initially. When there is a I/O request, the I/O device begins to transfer the interrupt to CPU. After the transfer is done, it requires some time for the CPU to be interrupted. The CPU stops user process executing and immediately transfers execution to a fixed location, in the timeline, that is I/O interrput processing. The fixed location usually contains the starting address where the service routine for the interrupt is located. The interrupt service routine executes; on completion, the CPU resumes the interrupted computation and comes back to user process executing.

![img_13.png](img_13.png)

(1)