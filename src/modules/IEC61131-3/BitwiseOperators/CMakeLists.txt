#*******************************************************************************
# Copyright (c) 2011 - 2014 ACIN, Profactor GmbH
# This program and the accompanying materials are made available under the
# terms of the Eclipse Public License 2.0 which is available at
# http://www.eclipse.org/legal/epl-2.0.
#
# SPDX-License-Identifier: EPL-2.0
# 
# Contributors:
#    Monika Wenger, Matthias Plasch
# *   - initial API and implementation and/or initial documentation
# *******************************************************************************/
forte_add_include_directories(${CMAKE_CURRENT_SOURCE_DIR})
#############################################################################
# BitwiseOperators
#############################################################################
forte_add_sourcefile_hcpp(F_AND_fbt)
forte_add_sourcefile_hcpp(F_NOT_fbt)
forte_add_sourcefile_hcpp(F_OR_fbt)
forte_add_sourcefile_hcpp(F_XOR_fbt)
forte_add_sourcefile_hcpp(genbitbase_fbt GEN_AND_fbt GEN_OR_fbt GEN_XOR_fbt)

forte_add_sourcefile_hcpp(F_SHL_fbt)
forte_add_sourcefile_hcpp(F_SHR_fbt)
forte_add_sourcefile_hcpp(F_ROR_fbt)
forte_add_sourcefile_hcpp(F_ROL_fbt)
