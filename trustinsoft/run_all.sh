#!/bin/bash

export ME=$(basename $0)
export DIR="$(dirname $0)"
export CONFIG="${DIR}/tis.json"
export LOGS="${PWD}/logs"
export RESULTS="${PWD}/_results"

if [ ! $(which jq) ]; then
   echo "Please install 'jq' to run $ME"
   exit 2
elif [ ! $(which parallel) ]; then
   echo "Please install 'parallel' to run $ME"
   exit 3
fi

if [ ! -f ${CONFIG} ]; then
   echo "Configuration file ${CONFIG} not found, exiting"
   exit 4
fi

function run_analysis {
   analysis_nbr="$1"
   opt=(
      -tis-config-load "${CONFIG}"
      -tis-config-select "${analysis_nbr}"
      -tis-report
      -save "_results/${analysis_nbr}.save"
   )
   tis-analyzer "${opt[@]}" | tee "${LOGS}/analysis.${analysis_nbr}.log"
}

function usage {

   cat << EOF
Usage: $ME [-n <n>] [-h]
Description: Runs multiple TrustInSoft analysis in parallel

-n: Defines the max number of parallel analysis, defaults to 1
-h: Displays this help and exits

Example:
$ME -n 5
EOF
   exit 1
}

export -f run_analysis
nbr_parallel_analyses=1

while [ $# -ne 0 ]; do
   case "${1}" in
      -n)
         shift
         nbr_parallel_analyses=${1}
         ;;
      *)
         echo "Wrong argument ${1}"
         usage
         ;;
   esac
   shift
done

nbr_analyses=$(jq '. | length' < ${CONFIG})

echo "Main config file = $CONFIG"
echo "Total nbr of analyses to run = $nbr_analyses"
echo "Nbr of analyses to run in parallel = $nbr_parallel_analyses"
mkdir -p "$LOGS"
if [ $nbr_parallel_analyses -le 1 ]; then
   echo "No parallel analysis, disabling usable of parallel"
   for i in $(seq 1 $nbr_analyses)
   do
      run_analysis $i
   done
else
   parallel -j $nbr_parallel_analyses run_analysis ::: $(seq 1 $nbr_analyses)
fi