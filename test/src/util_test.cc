///
/// @copyright Copyright (c)2016-, Issam SAID <said.issam@gmail.com>
/// All rights reserved.
///
/// Redistribution and use in source and binary forms, with or without
/// modification, are permitted provided that the following conditions
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
/// @file test/src/util_test.cc
/// @author Issam SAID
/// @brief Unit testing file for the urb_tree utilities.
/// 
#include <gtest/gtest.h>
#include <urb_tree/urb_tree.h>

namespace {

    int  int_cmp(void *a, void *b) { return *(int*)a-*(int*)b; }

    void int_dst(void *a) { free(a); }

    void int_shw(void *a, void *b) { 
        fprintf(stdout, "[%d, %d]\n", *(int*)a, *(int*)b); 
    }

    class UtilTest : public ::testing::Test {
    protected:
        virtual void SetUp() {
        }
        virtual void TearDown() { }
    };

    TEST_F(UtilTest, min) {
        urb_t *urb = &urb_sentinel;
        int i, T = 6;
        int *k, *v;
        for (i=1; i<=T; ++i) {
            k = (int*)malloc(sizeof(int));
            v = (int*)malloc(sizeof(int));
            *k = i;
            *v = i;
            ASSERT_EQ(urb_tree_put(&urb, urb_tree_create(k, v), int_cmp), 
                      URB_SUCCESS);
        }
        URB_TREE_CHECK_INVARIANTS(&urb);
        ASSERT_EQ(1, *(int*)urb_tree_min(&urb)->key);
        urb_tree_delete(&urb, int_dst, int_dst);
    }

    TEST_F(UtilTest, max) {
        urb_t *urb = &urb_sentinel;
        int i, T = 6;
        int *k, *v;
        for (i=1; i<=T; ++i) {
            k = (int*)malloc(sizeof(int));
            v = (int*)malloc(sizeof(int));
            *k = i;
            *v = i;
            ASSERT_EQ(urb_tree_put(&urb, urb_tree_create(k, v), int_cmp), 
                      URB_SUCCESS);
        }
        URB_TREE_CHECK_INVARIANTS(&urb);
        ASSERT_EQ(6, *(int*)urb_tree_max(&urb)->key);
        urb_tree_delete(&urb, int_dst, int_dst);
    }

    TEST_F(UtilTest, succ) {
        urb_t *urb = &urb_sentinel;
        urb_t *n   = &urb_sentinel;
        int tmp;
        int *k = (int*)malloc(sizeof(int));
        int *v = (int*)malloc(sizeof(int));
        *k = 8;
        *v = 8;
        ASSERT_EQ(urb_tree_put(&urb, urb_tree_create(k, v), int_cmp), URB_SUCCESS);
        k = (int*)malloc(sizeof(int));
        v = (int*)malloc(sizeof(int));
        *k = 5;
        *v = 5;
        ASSERT_EQ(urb_tree_put(&urb, urb_tree_create(k, v), int_cmp), URB_SUCCESS);
        k = (int*)malloc(sizeof(int));
        v = (int*)malloc(sizeof(int));
        *k = 2;
        *v = 2;
        ASSERT_EQ(urb_tree_put(&urb, urb_tree_create(k, v), int_cmp), URB_SUCCESS);
        k = (int*)malloc(sizeof(int));
        v = (int*)malloc(sizeof(int));
        *k = 1;
        *v = 1;
        ASSERT_EQ(urb_tree_put(&urb, urb_tree_create(k, v), int_cmp), URB_SUCCESS);
        k = (int*)malloc(sizeof(int));
        v = (int*)malloc(sizeof(int));
        *k = 14;
        *v = 14;
        ASSERT_EQ(urb_tree_put(&urb, urb_tree_create(k, v), int_cmp), URB_SUCCESS);
        k = (int*)malloc(sizeof(int));
        v = (int*)malloc(sizeof(int));
        *k = 7;
        *v = 7;
        ASSERT_EQ(urb_tree_put(&urb, urb_tree_create(k, v), int_cmp), URB_SUCCESS);
        k = (int*)malloc(sizeof(int));
        v = (int*)malloc(sizeof(int));
        *k = 11;
        *v = 11;
        ASSERT_EQ(urb_tree_put(&urb, urb_tree_create(k, v), int_cmp), URB_SUCCESS);
        k = (int*)malloc(sizeof(int));
        v = (int*)malloc(sizeof(int));
        *k = 12;
        *v = 12;
        ASSERT_EQ(urb_tree_put(&urb, urb_tree_create(k, v), int_cmp), URB_SUCCESS);
        URB_TREE_CHECK_INVARIANTS(&urb);
        tmp = 8;
        ASSERT_TRUE((n = urb_tree_find(&urb, &tmp, int_cmp)) != &urb_sentinel);
        ASSERT_EQ(11, *(int*)urb_tree_succ(n)->key);
        tmp = 11;
        ASSERT_TRUE((n = urb_tree_find(&urb, &tmp, int_cmp)) != &urb_sentinel);
        ASSERT_EQ(12, *(int*)urb_tree_succ(n)->key);
        tmp = 14;
        ASSERT_TRUE((n = urb_tree_find(&urb, &tmp, int_cmp)) != &urb_sentinel);
        ASSERT_EQ(NULL, urb_tree_succ(n));
        tmp = 5;
        ASSERT_TRUE((n = urb_tree_find(&urb, &tmp, int_cmp)) != &urb_sentinel);
        ASSERT_EQ(7, *(int*)urb_tree_succ(n)->key);
        urb_tree_delete(&urb, int_dst, int_dst);
    }

    TEST_F(UtilTest, prev) {
        urb_t *urb = &urb_sentinel;
        urb_t *n   = &urb_sentinel;
        int tmp;
        int *k = (int*)malloc(sizeof(int));
        int *v = (int*)malloc(sizeof(int));
        *k = 8;
        *v = 8;
        ASSERT_EQ(urb_tree_put(&urb, urb_tree_create(k, v), int_cmp), URB_SUCCESS);
        k = (int*)malloc(sizeof(int));
        v = (int*)malloc(sizeof(int));
        *k = 5;
        *v = 5;
        ASSERT_EQ(urb_tree_put(&urb, urb_tree_create(k, v), int_cmp), URB_SUCCESS);
        k = (int*)malloc(sizeof(int));
        v = (int*)malloc(sizeof(int));
        *k = 2;
        *v = 2;
        ASSERT_EQ(urb_tree_put(&urb, urb_tree_create(k, v), int_cmp), URB_SUCCESS);
        k = (int*)malloc(sizeof(int));
        v = (int*)malloc(sizeof(int));
        *k = 1;
        *v = 1;
        ASSERT_EQ(urb_tree_put(&urb, urb_tree_create(k, v), int_cmp), URB_SUCCESS);
        k = (int*)malloc(sizeof(int));
        v = (int*)malloc(sizeof(int));
        *k = 14;
        *v = 14;
        ASSERT_EQ(urb_tree_put(&urb, urb_tree_create(k, v), int_cmp), URB_SUCCESS);
        k = (int*)malloc(sizeof(int));
        v = (int*)malloc(sizeof(int));
        *k = 7;
        *v = 7;
        ASSERT_EQ(urb_tree_put(&urb, urb_tree_create(k, v), int_cmp), URB_SUCCESS);
        k = (int*)malloc(sizeof(int));
        v = (int*)malloc(sizeof(int));
        *k = 11;
        *v = 11;
        ASSERT_EQ(urb_tree_put(&urb, urb_tree_create(k, v), int_cmp), URB_SUCCESS);
        k = (int*)malloc(sizeof(int));
        v = (int*)malloc(sizeof(int));
        *k = 12;
        *v = 12;
        ASSERT_EQ(urb_tree_put(&urb, urb_tree_create(k, v), int_cmp), URB_SUCCESS);
        URB_TREE_CHECK_INVARIANTS(&urb);
        tmp = 8;
        ASSERT_TRUE((n = urb_tree_find(&urb, &tmp, int_cmp)) != &urb_sentinel);
        ASSERT_EQ(7, *(int*)urb_tree_prev(n)->key);
        tmp = 11;
        ASSERT_TRUE((n = urb_tree_find(&urb, &tmp, int_cmp)) != &urb_sentinel);
        ASSERT_EQ(8, *(int*)urb_tree_prev(n)->key);
        tmp = 14;
        ASSERT_TRUE((n = urb_tree_find(&urb, &tmp, int_cmp)) != &urb_sentinel);
        ASSERT_EQ(12, *(int*)urb_tree_prev(n)->key);
        tmp = 1;
        ASSERT_TRUE((n = urb_tree_find(&urb, &tmp, int_cmp)) != &urb_sentinel);
        ASSERT_EQ(NULL, urb_tree_prev(n));
        urb_tree_delete(&urb, int_dst, int_dst);
    }

    TEST_F(UtilTest, has) {
        urb_t *urb = &urb_sentinel, *n;
        int i, T = 6;
        int *k, *v, tmp;
        for (i=1; i<=T; ++i) {
            k = (int*)malloc(sizeof(int));
            v = (int*)malloc(sizeof(int));
            *k = i;
            *v = i;
            ASSERT_EQ(urb_tree_put(&urb, urb_tree_create(k, v), int_cmp), 
                      URB_SUCCESS);
        }
        URB_TREE_CHECK_INVARIANTS(&urb);
        tmp = 1;
        ASSERT_TRUE(urb_tree_has(&urb, &tmp, int_cmp, NULL));
        tmp = 2;
        ASSERT_TRUE(urb_tree_has(&urb, &tmp, int_cmp, NULL));
        tmp = 3;
        ASSERT_TRUE(urb_tree_has(&urb, &tmp, int_cmp, NULL));
        tmp = 4;
        ASSERT_TRUE(urb_tree_has(&urb, &tmp, int_cmp, NULL));
        tmp = 5;
        ASSERT_TRUE(urb_tree_has(&urb, &tmp, int_cmp, NULL));
        tmp = 6;
        ASSERT_TRUE(urb_tree_has(&urb, &tmp, int_cmp, &n));
        ASSERT_EQ(6, *(int*)n->value);
        urb_tree_delete(&urb, int_dst, int_dst);
    }

}  // namespace