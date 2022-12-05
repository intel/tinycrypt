#!/bin/bash

export FONT_BOLD=$(tput bold)
export FONT_CYAN=$(tput setaf 6)
export FONT_YELLOW=$(tput setaf 3)
export FONT_RESET=$(tput sgr0)
export ME=$(basename $0)
export DIR="$(dirname $0)"
export CONFIG="${DIR}/tis.json"
export LOGS="${PWD}/logs"
export RESULTS="${PWD}/_results"

if [ ! $(which jq) ]; then
   echo "Please install 'jq' to run $ME"
   exit 2
fi

if [ ! -f ${CONFIG} ]; then
   echo "Configuration file ${CONFIG} not found, exiting"
   exit 4
fi

function run_analysis {
   analysis_nbr="$1"
   analysis_name=$(jq ".[$analysis_nbr][\"name\"]" < ${CONFIG} | cut -d '"' -f 2)
   opt=(
      -tis-config-load "${CONFIG}"
      -tis-config-select "${analysis_nbr}"
      -tis-report
      -save "_results/${analysis_name}.save"
   )

   echo; echo "${FONT_CYAN}tis-analyzer ${opt[@]}${FONT_RESET}"; echo
   tis-analyzer "${opt[@]}" | tee "${LOGS}/analysis.${analysis_name}.log"
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

echo "${FONT_YELLOW}Main config file = $CONFIG"
echo "${FONT_YELLOW}Total nbr of analyses to run = $nbr_analyses"
echo "${FONT_YELLOW}Nbr of analyses to run in parallel = $nbr_parallel_analyses"
mkdir -p "$LOGS"
if [ $nbr_parallel_analyses -le 1 ]; then
   echo "No parallel analysis, disabling usable of parallel"
   for i in $(seq 1 $nbr_analyses)
   do
      run_analysis $i
   done
else
   if [ ! $(which parallel) ]; then
      echo "Please install 'parallel' to run $ME with more than 1 analysis in parallel"
      exit 3
   fi
   parallel -j $nbr_parallel_analyses run_analysis ::: $(seq 1 $nbr_analyses)
fi
