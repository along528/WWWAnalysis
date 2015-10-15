#!/bin/bash

# --- Setup ROOT ---
print '******************************************************************************'
print '*** Setting up ROOT **********************************************************'
print '******************************************************************************'
source $ATLAS_LOCAL_ROOT_BASE/user/atlasLocalSetup.sh
localSetupROOT --rootVersion=5.32.03-i686-slc5-gcc4.3
echo $ROOTSYS
print

# --- Check out and install RootCore ---
print '******************************************************************************'
print '*** Checking out RootCore ****************************************************'
print '******************************************************************************'
svn co svn+ssh://svn.cern.ch/reps/atlasoff/PhysicsAnalysis/D3PDTools/RootCore/tags/RootCore-00-01-17 RootCore
cd RootCore/
./configure
cd ..
print

# --- Setup RootCore ---
print '******************************************************************************'
print '*** Setting up RootCore ******************************************************'
print '******************************************************************************'
source RootCore/scripts/setup.sh
echo $ROOTCOREBIN
echo $ROOTCOREDIR
print

# --- Check out other packages ---
print '******************************************************************************'
print '*** Checking out other packages **********************************************'
print '******************************************************************************'
$ROOTCOREDIR/scripts/checkout.sh packages.txt
print

# --- Compile everything ---
$ROOTCOREDIR/scripts/find_packages.sh
$ROOTCOREDIR/scripts/compile.sh
