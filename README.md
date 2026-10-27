# servicescan

A small C++ program that scans lab subnets in parallel by running a PHP worker
script for each IP address, to get around PHP's lack of threads.

## What it does

It walks every address in a fixed list of subnets and starts a thread for each
one that runs a PHP script with the address. No more than five threads run at
once.

## Tech

- C++ with pthreads
- Eclipse CDT project (`Debug` holds the generated Makefile)

## Building

```sh
cd Debug
make
```

The subnets and the PHP script path are hardcoded in `src/servicescan.cpp`.

## License

Licensed under the Apache License 2.0. See [LICENSE](LICENSE).
