#ifndef __URB_TREE_LOG_H_
#define __URB_TREE_LOG_H_
///
/// @copyright Copyright (c)2016-, Issam SAID <said.issam@gmail.com>
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
/// FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
/// HOLDER OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
/// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
/// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
/// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
/// LIABILITY, WETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
/// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
/// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
///
/// @file urb_tree/log.h
/// @author Issam SAID
/// @brief Macros to format information or debug messages when using urb_tree.
///
#include <stdio.h>
#include <urb_tree/guard.h>
#include <urb_tree/colors.h>

CPPGUARD_BEGIN();

#ifdef  __URB_TEE_DEBUG
#define __URB_TREE_VERBOSE
#define URB_DEBUG(fmt,...)                                       \
fprintf(stdout, C_PURPLE"[URB_TREE DBG]: "fmt".\n"C_END, ##__VA_ARGS__)
#else 
#define URB_DEBUG(fmt,...) 
#endif  // __URB_TREE_DEBUG

#ifdef __URB_TREE_VERBOSE                             
#define URB_PRINT(fmt,...)                                      \
fprintf(stdout, C_GREEN"[URB_TREE MSG]: "fmt".\n"C_END, ##__VA_ARGS__)
#else 
#define URB_PRINT(fmt,...) 
#endif  // __URB_TREE_VERBOSE 

CPPGUARD_END();

#endif  // __URB_TREE_LOG_H_