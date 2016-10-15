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
/// @file examples/src/intger_string_urb/main.c
/// @author Issam SAID
/// @brief Implementation of an example of an intger/string Red-Black tree.
///
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <urb_tree/urb_tree.h>

///
/// @brief An array of global integer keys.
///
#define NB_KEYS 20
int keys[NB_KEYS] = { -1, -8,   9,   4, 17, -123, 15, 93, -76, 42, -47, 20, \
                      97, 111, 12, -31, -7,   26, 11, 19 };

///
/// @brief Delete the key of a given node.
///
void delete_key(void* k) { 
    fprintf(stdout, "... releasing key %d\n", *(int*)k); 
    free(k); 
}

///
/// @brief Delete the value of a given node.
///
void delete_value(void* v) { 
    fprintf(stdout, "... releasing value %s\n", (char*)v); 
    free(v); 
}

///
/// @brief A function to print the key/value of an entry in the tree.
///
void print_node(void *i, void *s) { 
    fprintf(stdout, "\tkey: %d, value: %s\n", *(int*)i, (char*)s); 
}

///
/// @brief A function used to compare integer keys.
///
int compare_integers(void *src, void *dst) { return *(int*)src - *(int*)dst; }

///
/// @brief Main function to show how to use <b>urb_tree</b> to implement 
/// an integer/string Red-Black tree.
///
/// @param Nothing.
/// @return Nothing.
///
int main( void) {
    urb_t *tree = &urb_sentinel;
    urb_t *node = &urb_sentinel;
    int    *key, my_key;
    char *value;
    unsigned int i;
    fprintf(stdout, "... Start integer/string tree example.\n");
    fprintf(stdout, "... Filling in the integer/string tree.\n");

    for (i=0; i< NB_KEYS; i++) {
        key   = (int*) malloc(sizeof(int));
        value = (char*)malloc(32*sizeof(char));
        *key  = keys[i];
        sprintf(value, "value_%d", *key);
        urb_tree_put(&tree, urb_tree_create(key, value), compare_integers);
    }
    URB_TREE_CHECK_INVARIANTS(&tree);
    fprintf(stdout, "... The tree size is: %ld.\n", urb_tree_size(&tree));    
    urb_tree_print(&tree, print_node);
    /*
    ulist_put(&list, ulist_create(create_string("foo", i)));
    my_string = create_string("my_string", 0);
    ulist_put(&list, ulist_create(my_string));
    for (i=22; i<=31; i++)
        ulist_put(&list, ulist_create(create_string("bar", i)));
    */
    my_key = 93;
    fprintf(stdout, "... Searching for one particular key in the tree.\n");
    node = urb_tree_find(&tree, &my_key, compare_integers);
    if (node != NULL) fprintf(stdout, "... Found.\n");
    fprintf(stdout, "... Retrieving that node from the tree.\n");
    node = urb_tree_pop(&tree, &my_key, compare_integers);
    urb_tree_print(&node, print_node);
    fprintf(stdout, 
            "... The tree size is now: %ld.\n", urb_tree_size(&tree));
    /*
    fprintf(stdout, 
            "... Walk through the list data and capitalize each string.\n");
    ulist_walk(&list, capitalize_string);
    ulist_print(&list, print_string);
    */
    fprintf(stdout, "... Emptying the tree.\n");
    urb_tree_delete(&tree, delete_key, delete_value);
    
    fprintf(stdout, "... End integer/string tree example.\n");
    return EXIT_SUCCESS;
}