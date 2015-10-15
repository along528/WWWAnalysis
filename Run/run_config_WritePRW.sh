#!/bin/zsh

electronconfig=$1
muonconfig=$2
eventconfig=$3
outdir=$4
scandir=$5
sysflag=$6

root -l -b -q  'analyze_Config_WritePRW.cxx ("'$electronconfig'","'$muonconfig'","'$eventconfig'","'$outdir'","'$scandir'","'$sysflag'")';
#root -l -b -q 'printfile.cxx ("'test$num'/data-outFile/user.xchen.mc12_8TeV.161595.PowHegPythia8_VBFH125_tautaull.NTUP_TAU.e1222_s1469_s1470_r3542_r3549_p1344_hsg4llv1.130127142304.root")'
#root -l -b -q 'printfile.cxx ("'test$num'/data-outFile/user.xin.data12_8TeV.testSample.root")'
