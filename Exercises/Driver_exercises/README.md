# Linux Character Device Driver Exercises

This folder contains exercises for implementing and using a Linux character device driver. The kernel module (`simple.c`) exposes device operations to user space; the accompanying user-space programs open the device and exchange data through the driver's kernel memory.

## Requirements

- Linux with kernel headers matching the running kernel
- Build tools (`make`, `gcc`/`g++`)
- Administrator privileges to load the kernel module and create device nodes

> **Warning:** Loading kernel modules requires care. Test on a disposable virtual machine if possible, and make sure the module is compatible with your running kernel.

## Exercise 1 — Basic character device and data exchange

Start with the files in `Solution/` as the reference implementation. The exercise involves completing the driver and the user-space `read.c` and `write.c` programs.

The general workflow, from the directory containing the relevant `Makefile`, is:

1. Build the module:

   ```bash
   make
   ```

2. Load it (administrator privileges required):

   ```bash
   sudo insmod simple.ko
   ```

3. Find the assigned major number. Depending on the kernel/system, inspect the kernel log or the registered character devices; the original exercise handout suggests:

   ```bash
   cat /proc/devices
   ```

4. Create the device node using the major number reported for `simple` and minor number `0`:

   ```bash
   sudo mknod /dev/simple c <major> 0
   ```

5. Compile the user-space programs:

   ```bash
   gcc read.c -o read
   gcc write.c -o write
   ```

   If using the reference files named `read-final.c` and `write-final.c`, substitute those filenames in the commands.

6. Run the writer first, then the reader (in separate terminals if needed):

   ```bash
   ./write
   ./read
   ```

The reader must be run after the writer in the basic example, because the data is stored in the driver's shared kernel buffer. When finished, unload the module with `sudo rmmod simple` and remove the device node with `sudo rm /dev/simple`.

## Additional implementations

- **`Solution/`** — reference solution for the basic character-device exercise.
- **`SolutionBlocking/`** — adds blocking read behaviour. A read operation waits until data is available; running the reader before the writer therefore causes it to wait. Compare this with non-blocking operation (`O_NONBLOCK`).
- **`SolutionMinor/`** — extends the driver to handle two memory areas through two minor numbers, with separate file-operation handling. Create and use a device node for each minor number to access the corresponding area.

Each solution directory contains its own `Makefile` and source files. Build and load only one implementation at a time, and unload an already-loaded module before replacing it.

## What to study

- Character-device registration and major/minor numbers.
- The `open`, `read`, and `write` file operations.
- Data transfer between kernel space and user space.
- Device-node creation with `mknod`.
- Blocking versus non-blocking I/O.
- Multiple minor numbers and per-device state.
