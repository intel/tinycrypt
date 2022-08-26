# tinycrypt library analysis with **TrustInSoft Analyzer**

This repository demonstrates the tinycrypt library analysis with **TrustInSoft Analyzer**.

It is a fork of [Intel tinycrypt library](https://github.com/intel/tinycrypt) supplemented to integrate
the TrustInSoft analysis

## Prerequisites
- Run on Unbuntu (16.04 18.04 20.04). 22.04 Should also work without guarantee
- `bear` tool installed. See https://installati.one/ubuntu/20.04/bear/
- `tis-analyzer` package installed with access to a valid license (FlexNet or Node locked)

## Running analysis
- Build the code, wrapping with `bear` to produce a compilation database

`bear make clean all`

  This builds the code and produces the `compile_commands.json` compilation database
  (You make have a look at the original library [README](./README)) if you are curious

- Run the **TrustInSoft** analysis

`make -f tis.mk clean tis`

  (You make have a look at the [tis.mk](./tis.mk) makefile if you are curious)

  This runs the **TrustInSoft** analyzer and produces an `tis-issues.log` file

  - If no issues were found the `make` commands succeeds and returns 0
  - If some issues were found and file `tis-issues.log` is not empty, then the `make` commands fails with and error status code.
    A normal run should be in that case (22 issues should be found)

## Enjoy !