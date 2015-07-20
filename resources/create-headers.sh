#/bin/env zsh
cd head

printline () {
  filepath=$1
  linecout=$2
  #echo $1 $2 $3
  tailnum=$(expr $2 - $3 + 1)
  #tailnum=$(expr $2 + 1 + $3)
  #echo $tailnum
  tail -n $tailnum $filepath| head -n 1
  #echo "lulwat $tailnum"
}

for dir in `ls`;do
  if [ -d $PWD/$dir ]; then
    for file in `ls $PWD/$dir`;do
      if [ -f $PWD/$dir/$file ]; then 
        thefile=$PWD/$dir/$file 
        numlines=`wc -l $thefile |cut -d' ' -f 1`
        #cat $thefile
        #echo $thefile
        
        for line in `seq 1 $numlines`; do
          #linedata=`sed -n "$line,$line p" $thefile`
          lul=printline $thefile $nums $line

          echo $lul >> ../lulwat


          #echo $ha
          ##doublebackslash=$(echo -E $linedata | sed 's.\\.\\\\.g')
          #help=$(echo -e"       hah")
          #echo $linedata
          #echo $help >> ../lul.wat
          
          #echo "cafy $cafy"  
          #echo -E " $line of $thefile $linedata" 
        done
      fi
    done  
  fi
done

