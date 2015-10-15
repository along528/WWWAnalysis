#!/bin/zsh
num=1
while [[ -d /data/lhelary/Preselection/Cutflow_Data$num ]] ; do
    let num++
done

echo $num

#root -l -b -q 'analyze.cxx ("'test$num'")';
#root -l -b -q  'analyze.cxx ("'test1'")';
#root -l -b -q 'printfile.cxx ("'test$num'/data-outFile/user.xchen.mc12_8TeV.161595.PowHegPythia8_VBFH125_tautaull.NTUP_TAU.e1222_s1469_s1470_r3542_r3549_p1344_hsg4llv1.130127142304.root")'
#root -l -b -q 'printfile.cxx ("'test$num'/data-outFile/user.xin.data12_8TeV.testSample.root")'
#python printCutFlows.py test$num>>test$num.out
#diff test$num.out ConvergedCutFlows.txt
#rm test$num.out

#./run_config.sh HW_Custom  HW_Custom Baseline_Preselection jobs/Preselection/Cutflow_Data 2LeptonSkims

./run_config.sh HW_Custom_NoIsolCuts  HW_Custom_NoIsolCuts Baseline_Preselection /data/lhelary/Preselection/Cutflow_Data$num Signal
