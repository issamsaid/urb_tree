#ifndef __URB_TREE_ERROR_H_
#define __URB_TREE_ERROR_H_
///
/// @copyright Copyright (c) 2016-, Issam SAID <said.issam@gmail.com>.
/// All rights reserved.
///
/// Redistribution and use in source and binary forms, with or without
/// modification, are permetted provided that the following conditions
/// are met:
///
/// 1. Redistributions of source code must retain the above copyright
///    notice, this list of conditions and the following disclaimer.
/// 2. Redistributions in binary form must reproduce the above copyright
///    notice, this list of conditions and the following disclaimer in the
///    documentation and/or other materials provided with the distribution.
/// 3. Neither the name of the copyright holder nor the names of its contributors
///    may be used to endorse or promote products derived from this software
///    without specific prior written permission.
///
/// THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
/// INCLUDING, BUT NOT LIMITED TO, WARRANTIES OF MERCHANTABILITY AND FITNESS
/// FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE copyright holder OR
/// ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
/// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
/// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
/// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
/// LIABILITY, WETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
/// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
/// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
///
/// @file urb_tree/error.h
/// @author Issam SAID
/// @brief ulist error handling routines and macros.    
///
#include <stdio.h>
#include <stdlib.h>
#include <urb_tree/guard.h>
#include <urb_tree/colors.h>

CPPGUARD_BEGIN();

#define URB_SUCCESS          0
#define URB_OUT_OF_MEMORY   -1
#define URB_INVALID_NODE    -2
#define URB_INVALID_VALUE   -3
#define URB_DUPLICATE_KEY   -4

#define URB_EXIT(error_code, fmt,...)                                     \
{                                                                         \
    fprintf(stderr, C_RED"[URB_TREE ERR(%s)]: "fmt" @%s:%d.\n"C_END,      \
            URB_ERROR_MSG(error_code),##__VA_ARGS__, __FILE__, __LINE__); \
    exit(error_code);                                                     \
}

#define URB_ERROR_MSG(error_code)                                   \
    ((error_code == URB_SUCCESS)         ? "URB_SUCCESS"          : \
     (error_code == URB_OUT_OF_MEMORY)   ? "URB_OUT_OF_MEMORY"    : \
     (error_code == URB_INVALID_NODE)    ? "URB_INVALID_NODE"     : \
     (error_code == URB_INVALID_VALUE)   ? "URB_INVALID_VALUE"    : \
     (error_code == URB_DUPLICATE_KEY)   ? "URB_DUPLICATE_KEY"    : \
    "URB_TREE_UNKNOWN")

CPPGUARD_END();

#endif  // __URB_TREE_ERROR_H_