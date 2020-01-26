import sys
sys.path.append('/Users/jtoumey/CodeRepositories/active/prePostProcessLib
/openFoamLib')

import foamDictTools as fdt
import blockMeshDictTools as bmdt



test_file_handle = 'blockMeshDict'
test_file = fdt.OfDict(test_file_handle)
