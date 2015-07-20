#/bin/env zsh
cd head

printline () {
  filepath=$1
  linecout=$2
  tailnum=$(expr $2 - $3 + 1)
  tail -n $tailnum $filepath| head -n 1
}

for dir in `ls`;do
  if [ -d $PWD/$dir ]; then
    for file in `ls $PWD/$dir`;do
      if [ -f $PWD/$dir/$file ]; then 
        thefile=$PWD/$dir/$file 
        numlines=`wc -l $thefile |cut -d' ' -f 1`
        for line in `seq 1 $numlines`; do
          printline $thefile $nums $line | sed 's.\\.\\\\.g'
          echo $ha
        done
      fi
    done  
  fi
done

