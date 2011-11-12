/* /////////////////////////////////////////////////////////
 * includes
 */
#include "tbox.h"

/* /////////////////////////////////////////////////////////
 * macros
 */

#define TB_DLIST_GROW_SIZE 			(256)

/* /////////////////////////////////////////////////////////
 * details
 */

static tb_void_t tb_dlist_int_dump(tb_dlist_t const* dlist)
{
	tb_trace("size: %d, maxn: %d", tb_dlist_size(dlist), tb_dlist_maxn(dlist));
	tb_size_t itor = tb_dlist_itor_head(dlist);
	tb_size_t tail = tb_dlist_itor_tail(dlist);
	for (; itor != tail; itor = tb_dlist_itor_next(dlist, itor))
	{
		tb_size_t item = (tb_size_t)tb_dlist_itor_const_at(dlist, itor);
		tb_trace("at[%d]: %x", itor, item);
	}
}
static tb_size_t tb_dlist_insert_test()
{
	// init
	tb_dlist_t* dlist = tb_dlist_init(TB_DLIST_GROW_SIZE, tb_item_func_int());
	tb_assert_and_check_return_val(dlist, 0);

	// insert one first
	tb_size_t itor = tb_dlist_insert_head(dlist, 0xd);

	__tb_volatile__ tb_size_t i = 0;
	__tb_volatile__ tb_size_t n = 10000;
	tb_int64_t t = tb_mclock();
	for (i = 0; i < n; i++) tb_dlist_insert(dlist, itor, 0xd);
	t = tb_int64_sub(tb_mclock(), t);

	// time
	tb_trace("tb_dlist_insert(%d): %lld ms, size: %d, maxn: %d", n, t, tb_dlist_size(dlist), tb_dlist_maxn(dlist));

	// check
	tb_assert(tb_dlist_size(dlist) == n + 1);
	tb_assert(tb_dlist_const_at_head(dlist) == 0xd);
	tb_assert(tb_dlist_const_at_last(dlist) == 0xd);

	// clear it
	tb_dlist_clear(dlist);
	tb_assert(!tb_dlist_size(dlist));

	// exit
	tb_dlist_exit(dlist);

	return n / (tb_int64_to_int32(t) + 1);
}
static tb_size_t tb_dlist_insert_head_test()
{
	// init
	tb_dlist_t* dlist = tb_dlist_init(TB_DLIST_GROW_SIZE, tb_item_func_int());
	tb_assert_and_check_return_val(dlist, 0);

	__tb_volatile__ tb_size_t i = 0;
	__tb_volatile__ tb_size_t n = 1000000;
	tb_int64_t t = tb_mclock();
	for (i = 0; i < n; i++) tb_dlist_insert_head(dlist, 0xd);
	t = tb_int64_sub(tb_mclock(), t);

	// time
	tb_trace("tb_dlist_insert_head(%d): %lld ms, size: %d, maxn: %d", n, t, tb_dlist_size(dlist), tb_dlist_maxn(dlist));

	// check
	tb_assert(tb_dlist_size(dlist) == n);
	tb_assert(tb_dlist_const_at_head(dlist) == 0xd);
	tb_assert(tb_dlist_const_at_last(dlist) == 0xd);

	// clear it
	tb_dlist_clear(dlist);
	tb_assert(!tb_dlist_size(dlist));

	// exit
	tb_dlist_exit(dlist);
	
	return n / (tb_int64_to_int32(t) + 1);
}
static tb_size_t tb_dlist_insert_tail_test()
{
	// init
	tb_dlist_t* dlist = tb_dlist_init(TB_DLIST_GROW_SIZE, tb_item_func_int());
	tb_assert_and_check_return_val(dlist, 0);

	__tb_volatile__ tb_size_t i = 0;
	__tb_volatile__ tb_size_t n = 1000000;
	tb_int64_t t = tb_mclock();
	for (i = 0; i < n; i++) tb_dlist_insert_tail(dlist, 0xd);
	t = tb_int64_sub(tb_mclock(), t);

	// time
	tb_trace("tb_dlist_insert_tail(%d): %lld ms, size: %d, maxn: %d", n, t, tb_dlist_size(dlist), tb_dlist_maxn(dlist));

	// check
	tb_assert(tb_dlist_size(dlist) == n);
	tb_assert(tb_dlist_const_at_head(dlist) == 0xd);
	tb_assert(tb_dlist_const_at_last(dlist) == 0xd);

	// clear it
	tb_dlist_clear(dlist);
	tb_assert(!tb_dlist_size(dlist));

	// exit
	tb_dlist_exit(dlist);

	return n / (tb_int64_to_int32(t) + 1);
}
static tb_size_t tb_dlist_ninsert_test()
{
	// init
	tb_dlist_t* dlist = tb_dlist_init(TB_DLIST_GROW_SIZE, tb_item_func_int());
	tb_assert_and_check_return_val(dlist, 0);

	// insert one first
	tb_size_t itor = tb_dlist_insert_head(dlist, 0xd);

	tb_size_t n = 1000000;
	tb_int64_t t = tb_mclock();
	tb_dlist_ninsert(dlist, itor, 0xd, n);
	t = tb_int64_sub(tb_mclock(), t);

	// time
	tb_trace("tb_dlist_ninsert(%d): %lld ms, size: %d, maxn: %d", n, t, tb_dlist_size(dlist), tb_dlist_maxn(dlist));

	// check
	tb_assert(tb_dlist_size(dlist) == n + 1);
	tb_assert(tb_dlist_const_at_head(dlist) == 0xd);
	tb_assert(tb_dlist_const_at_last(dlist) == 0xd);

	// clear it
	tb_dlist_clear(dlist);
	tb_assert(!tb_dlist_size(dlist));

	// exit
	tb_dlist_exit(dlist);

	return n / (tb_int64_to_int32(t) + 1);
}
static tb_size_t tb_dlist_ninsert_head_test()
{
	// init
	tb_dlist_t* dlist = tb_dlist_init(TB_DLIST_GROW_SIZE, tb_item_func_int());
	tb_assert_and_check_return_val(dlist, 0);

	tb_size_t n = 1000000;
	tb_int64_t t = tb_mclock();
	tb_dlist_ninsert_head(dlist, 0xd, n);
	t = tb_int64_sub(tb_mclock(), t);

	// time
	tb_trace("tb_dlist_ninsert_head(%d): %lld ms, size: %d, maxn: %d", n, t, tb_dlist_size(dlist), tb_dlist_maxn(dlist));

	// check
	tb_assert(tb_dlist_size(dlist) == n);
	tb_assert(tb_dlist_const_at_head(dlist) == 0xd);
	tb_assert(tb_dlist_const_at_last(dlist) == 0xd);

	// clear it
	tb_dlist_clear(dlist);
	tb_assert(!tb_dlist_size(dlist));

	// exit
	tb_dlist_exit(dlist);

	return n / (tb_int64_to_int32(t) + 1);
}
static tb_size_t tb_dlist_ninsert_tail_test()
{
	// init
	tb_dlist_t* dlist = tb_dlist_init(TB_DLIST_GROW_SIZE, tb_item_func_int());
	tb_assert_and_check_return_val(dlist, 0);

	tb_size_t n = 1000000;
	tb_int64_t t = tb_mclock();
	tb_dlist_ninsert_tail(dlist, 0xd, n);
	t = tb_int64_sub(tb_mclock(), t);

	// time
	tb_trace("tb_dlist_ninsert_tail(%d): %lld ms, size: %d, maxn: %d", n, t, tb_dlist_size(dlist), tb_dlist_maxn(dlist));

	// check
	tb_assert(tb_dlist_size(dlist) == n);
	tb_assert(tb_dlist_const_at_head(dlist) == 0xd);
	tb_assert(tb_dlist_const_at_last(dlist) == 0xd);

	// clear it
	tb_dlist_clear(dlist);
	tb_assert(!tb_dlist_size(dlist));

	// exit
	tb_dlist_exit(dlist);

	return n / (tb_int64_to_int32(t) + 1);
}
static tb_size_t tb_dlist_remove_test()
{
	// init
	tb_dlist_t* dlist = tb_dlist_init(TB_DLIST_GROW_SIZE, tb_item_func_int());
	tb_assert_and_check_return_val(dlist, 0);

	__tb_volatile__ tb_size_t i = 0;
	__tb_volatile__ tb_size_t n = 1000000;
	tb_size_t itor = tb_dlist_ninsert_head(dlist, 0xd, n);
	tb_int64_t t = tb_mclock();
	for (i = 0; i < n; i++) itor = tb_dlist_remove(dlist, itor);
	t = tb_int64_sub(tb_mclock(), t);

	// time
	tb_trace("tb_dlist_remove(%d): %lld ms, size: %d, maxn: %d", n, t, tb_dlist_size(dlist), tb_dlist_maxn(dlist));

	// check
	tb_assert(!tb_dlist_size(dlist));

	// exit
	tb_dlist_exit(dlist);

	return n / (tb_int64_to_int32(t) + 1);
}
static tb_size_t tb_dlist_remove_head_test()
{
	// init
	tb_dlist_t* dlist = tb_dlist_init(TB_DLIST_GROW_SIZE, tb_item_func_int());
	tb_assert_and_check_return_val(dlist, 0);

	__tb_volatile__ tb_size_t i = 0;
	__tb_volatile__ tb_size_t n = 1000000;
	tb_size_t itor = tb_dlist_ninsert_head(dlist, 0xd, n);
	tb_int64_t t = tb_mclock();
	for (i = 0; i < n; i++) tb_dlist_remove_head(dlist);
	t = tb_int64_sub(tb_mclock(), t);

	// time
	tb_trace("tb_dlist_remove_head(%d): %lld ms, size: %d, maxn: %d", n, t, tb_dlist_size(dlist), tb_dlist_maxn(dlist));

	// check
	tb_assert(!tb_dlist_size(dlist));

	// exit
	tb_dlist_exit(dlist);
}
static tb_size_t tb_dlist_remove_last_test()
{
	// init
	tb_dlist_t* dlist = tb_dlist_init(TB_DLIST_GROW_SIZE, tb_item_func_int());
	tb_assert_and_check_return_val(dlist, 0);

	__tb_volatile__ tb_size_t i = 0;
	__tb_volatile__ tb_size_t n = 10000;
	tb_size_t itor = tb_dlist_ninsert_head(dlist, 0xd, n);
	tb_int64_t t = tb_mclock();
	for (i = 0; i < n; i++) tb_dlist_remove_last(dlist);
	t = tb_int64_sub(tb_mclock(), t);

	// time
	tb_trace("tb_dlist_remove_last(%d): %lld ms, size: %d, maxn: %d", n, t, tb_dlist_size(dlist), tb_dlist_maxn(dlist));

	// check
	tb_assert(!tb_dlist_size(dlist));

	// exit
	tb_dlist_exit(dlist);

	return n / (tb_int64_to_int32(t) + 1);
}
static tb_size_t tb_dlist_nremove_test()
{
	// init
	tb_dlist_t* dlist = tb_dlist_init(TB_DLIST_GROW_SIZE, tb_item_func_int());
	tb_assert_and_check_return_val(dlist, 0);

	tb_size_t n = 1000000;
	tb_size_t itor = tb_dlist_ninsert_head(dlist, 0xd, n);
	tb_int64_t t = tb_mclock();
	tb_dlist_nremove(dlist, tb_dlist_itor_head(dlist), n);
	t = tb_int64_sub(tb_mclock(), t);

	// time
	tb_trace("tb_dlist_nremove(%d): %lld ms, size: %d, maxn: %d", n, t, tb_dlist_size(dlist), tb_dlist_maxn(dlist));

	// check
	tb_assert(!tb_dlist_size(dlist));

	// exit
	tb_dlist_exit(dlist);

	return n / (tb_int64_to_int32(t) + 1);
}
static tb_size_t tb_dlist_nremove_head_test()
{
	// init
	tb_dlist_t* dlist = tb_dlist_init(TB_DLIST_GROW_SIZE, tb_item_func_int());
	tb_assert_and_check_return_val(dlist, 0);

	tb_size_t n = 1000000;
	tb_size_t itor = tb_dlist_ninsert_head(dlist, 0xd, n);
	tb_int64_t t = tb_mclock();
	tb_dlist_nremove_head(dlist, n);
	t = tb_int64_sub(tb_mclock(), t);

	// time
	tb_trace("tb_dlist_nremove_head(%d): %lld ms, size: %d, maxn: %d", n, t, tb_dlist_size(dlist), tb_dlist_maxn(dlist));

	// check
	tb_assert(!tb_dlist_size(dlist));

	// exit
	tb_dlist_exit(dlist);

	return n / (tb_int64_to_int32(t) + 1);
}
static tb_size_t tb_dlist_nremove_last_test()
{
	// init
	tb_dlist_t* dlist = tb_dlist_init(TB_DLIST_GROW_SIZE, tb_item_func_int());
	tb_assert_and_check_return_val(dlist, 0);

	tb_size_t n = 1000000;
	tb_size_t itor = tb_dlist_ninsert_head(dlist, 0xd, n);
	tb_int64_t t = tb_mclock();
	tb_dlist_nremove_last(dlist, n);
	t = tb_int64_sub(tb_mclock(), t);

	// time
	tb_trace("tb_dlist_nremove_last(%d): %lld ms, size: %d, maxn: %d", n, t, tb_dlist_size(dlist), tb_dlist_maxn(dlist));

	// check
	tb_assert(!tb_dlist_size(dlist));

	// exit
	tb_dlist_exit(dlist);

	return n / (tb_int64_to_int32(t) + 1);
}
static tb_size_t tb_dlist_replace_test()
{
	// init
	tb_dlist_t* dlist = tb_dlist_init(TB_DLIST_GROW_SIZE, tb_item_func_int());
	tb_assert_and_check_return_val(dlist, 0);

	tb_size_t n = 1000000;
	tb_dlist_ninsert_head(dlist, 0xd, n);
	tb_size_t itor = tb_dlist_itor_head(dlist);
	tb_size_t tail = tb_dlist_itor_tail(dlist);
	tb_int64_t t = tb_mclock();
	for (; itor != tail; itor = tb_dlist_itor_next(dlist, itor)) tb_dlist_replace(dlist, itor, 0xe);
	t = tb_int64_sub(tb_mclock(), t);

	// time
	tb_trace("tb_dlist_replace(%d): %lld ms, size: %d, maxn: %d", n, t, tb_dlist_size(dlist), tb_dlist_maxn(dlist));

	// check
	tb_assert(tb_dlist_size(dlist) == n);
	tb_assert(tb_dlist_const_at_head(dlist) == 0xe);
	tb_assert(tb_dlist_const_at_last(dlist) == 0xe);

	// exit
	tb_dlist_exit(dlist);

	return n / (tb_int64_to_int32(t) + 1);
}
static tb_size_t tb_dlist_replace_head_test()
{
	// init
	tb_dlist_t* dlist = tb_dlist_init(TB_DLIST_GROW_SIZE, tb_item_func_int());
	tb_assert_and_check_return_val(dlist, 0);

	__tb_volatile__ tb_size_t i = 0;
	__tb_volatile__ tb_size_t n = 1000000;
	tb_size_t itor = tb_dlist_ninsert_head(dlist, 0xd, n);
	tb_int64_t t = tb_mclock();
	for (i = 0; i < n; i++) tb_dlist_replace_head(dlist, 0xe);
	t = tb_int64_sub(tb_mclock(), t);

	// time
	tb_trace("tb_dlist_replace_head(%d): %lld ms, size: %d, maxn: %d", n, t, tb_dlist_size(dlist), tb_dlist_maxn(dlist));

	// check
	tb_assert(tb_dlist_size(dlist) == n);
	tb_assert(tb_dlist_const_at_head(dlist) == 0xe);

	// exit
	tb_dlist_exit(dlist);

	return n / (tb_int64_to_int32(t) + 1);
}
static tb_size_t tb_dlist_replace_last_test()
{
	// init
	tb_dlist_t* dlist = tb_dlist_init(TB_DLIST_GROW_SIZE, tb_item_func_int());
	tb_assert_and_check_return_val(dlist, 0);

	__tb_volatile__ tb_size_t i = 0;
	__tb_volatile__ tb_size_t n = 1000000;
	tb_size_t itor = tb_dlist_ninsert_head(dlist, 0xd, n);
	tb_int64_t t = tb_mclock();
	for (i = 0; i < n; i++) tb_dlist_replace_last(dlist, 0xe);
	t = tb_int64_sub(tb_mclock(), t);

	// time
	tb_trace("tb_dlist_replace_last(%d): %lld ms, size: %d, maxn: %d", n, t, tb_dlist_size(dlist), tb_dlist_maxn(dlist));

	// check
	tb_assert(tb_dlist_size(dlist) == n);
	tb_assert(tb_dlist_const_at_last(dlist) == 0xe);


	// exit
	tb_dlist_exit(dlist);

	return n / (tb_int64_to_int32(t) + 1);
}
static tb_size_t tb_dlist_nreplace_test()
{
	// init
	tb_dlist_t* dlist = tb_dlist_init(TB_DLIST_GROW_SIZE, tb_item_func_int());
	tb_assert_and_check_return_val(dlist, 0);

	tb_size_t n = 1000000;
	tb_size_t itor = tb_dlist_ninsert_head(dlist, 0xd, n);
	tb_int64_t t = tb_mclock();
	tb_dlist_nreplace(dlist, tb_dlist_itor_head(dlist), 0xe, n);
	t = tb_int64_sub(tb_mclock(), t);

	// time
	tb_trace("tb_dlist_nreplace(%d): %lld ms, size: %d, maxn: %d", n, t, tb_dlist_size(dlist), tb_dlist_maxn(dlist));

	// check
	tb_assert(tb_dlist_size(dlist) == n);
	tb_assert(tb_dlist_const_at_head(dlist) == 0xe);
	tb_assert(tb_dlist_const_at_last(dlist) == 0xe);

	// exit
	tb_dlist_exit(dlist);

	return n / (tb_int64_to_int32(t) + 1);
}
static tb_size_t tb_dlist_nreplace_head_test()
{
	// init
	tb_dlist_t* dlist = tb_dlist_init(TB_DLIST_GROW_SIZE, tb_item_func_int());
	tb_assert_and_check_return_val(dlist, 0);

	tb_size_t n = 1000000;
	tb_size_t itor = tb_dlist_ninsert_head(dlist, 0xd, n);
	tb_int64_t t = tb_mclock();
	tb_dlist_nreplace_head(dlist, 0xe, n);
	t = tb_int64_sub(tb_mclock(), t);

	// time
	tb_trace("tb_dlist_nreplace_head(%d): %lld ms, size: %d, maxn: %d", n, t, tb_dlist_size(dlist), tb_dlist_maxn(dlist));

	// check
	tb_assert(tb_dlist_size(dlist) == n);
	tb_assert(tb_dlist_const_at_head(dlist) == 0xe);
	tb_assert(tb_dlist_const_at_last(dlist) == 0xe);

	// exit
	tb_dlist_exit(dlist);

	return n / (tb_int64_to_int32(t) + 1);
}
static tb_size_t tb_dlist_nreplace_last_test()
{
	// init
	tb_dlist_t* dlist = tb_dlist_init(TB_DLIST_GROW_SIZE, tb_item_func_int());
	tb_assert_and_check_return_val(dlist, 0);

	tb_size_t n = 1000000;
	tb_size_t itor = tb_dlist_ninsert_head(dlist, 0xd, n);
	tb_int64_t t = tb_mclock();
	tb_dlist_nreplace_last(dlist, 0xe, n);
	t = tb_int64_sub(tb_mclock(), t);

	// time
	tb_trace("tb_dlist_nreplace_last(%d): %lld ms, size: %d, maxn: %d", n, t, tb_dlist_size(dlist), tb_dlist_maxn(dlist));

	// check
	tb_assert(tb_dlist_size(dlist) == n);
	tb_assert(tb_dlist_const_at_head(dlist) == 0xe);
	tb_assert(tb_dlist_const_at_last(dlist) == 0xe);


	// exit
	tb_dlist_exit(dlist);

	return n / (tb_int64_to_int32(t) + 1);
}

static tb_size_t tb_dlist_iterator_next_test()
{
	// init
	tb_dlist_t* dlist = tb_dlist_init(TB_DLIST_GROW_SIZE, tb_item_func_int());
	tb_assert_and_check_return_val(dlist, 0);

	tb_size_t n = 1000000;
	tb_dlist_ninsert_head(dlist, 0xd, n);
	__tb_volatile__ tb_size_t itor = tb_dlist_itor_head(dlist);
	__tb_volatile__ tb_size_t tail = tb_dlist_itor_tail(dlist);
	tb_int64_t t = tb_mclock();
	for (; itor != tail; itor = tb_dlist_itor_next(dlist, itor))
	{
		__tb_volatile__ tb_byte_t const* item = tb_dlist_itor_const_at(dlist, itor);
	}
	t = tb_int64_sub(tb_mclock(), t);

	// time
	tb_trace("tb_dlist_iterator_next(%d): %lld ms, size: %d, maxn: %d", n, t, tb_dlist_size(dlist), tb_dlist_maxn(dlist));

	// exit
	tb_dlist_exit(dlist);

	return n / (tb_int64_to_int32(t) + 1);
}
static tb_size_t tb_dlist_iterator_prev_test()
{
	// init
	tb_dlist_t* dlist = tb_dlist_init(TB_DLIST_GROW_SIZE, tb_item_func_int());
	tb_assert_and_check_return_val(dlist, 0);

	tb_size_t n = 10000;
	tb_dlist_ninsert_head(dlist, 0xd, n);
	__tb_volatile__ tb_size_t itor = tb_dlist_itor_last(dlist);
	__tb_volatile__ tb_size_t head = tb_dlist_itor_head(dlist);
	tb_int64_t t = tb_mclock();
	while (1)
	{
		__tb_volatile__ tb_byte_t const* item = tb_dlist_itor_const_at(dlist, itor);

		if (itor == head) break;
		itor = tb_dlist_itor_prev(dlist, itor);
	}
	t = tb_int64_sub(tb_mclock(), t);

	// time
	tb_trace("tb_dlist_iterator_prev(%d): %lld ms, size: %d, maxn: %d", n, t, tb_dlist_size(dlist), tb_dlist_maxn(dlist));

	// exit
	tb_dlist_exit(dlist);

	return n / (tb_int64_to_int32(t) + 1);
}
/* /////////////////////////////////////////////////////////
 * main
 */
int main(int argc, char** argv)
{
	if (!tb_init(malloc(30 * 1024 * 1024), 30 * 1024 * 1024)) return 0;

	// init dlist
	tb_dlist_t* dlist = tb_dlist_init(TB_DLIST_GROW_SIZE, tb_item_func_int());
	tb_assert_and_check_goto(dlist, end);

	tb_size_t 			i = 0;
	tb_size_t 			j = 0;

	tb_trace("=============================================================");
	tb_trace("insert:");
	tb_dlist_ninsert_head(dlist, 0xa, 10);
	i = tb_dlist_ninsert_tail(dlist, 0xf, 10);
	j = tb_dlist_insert(dlist, i, 0);
	tb_dlist_insert(dlist, i, 1);
	tb_dlist_insert(dlist, i, 2);
	tb_dlist_insert(dlist, i, 3);
	tb_dlist_insert(dlist, i, 4);
	tb_dlist_insert(dlist, i, 5);
	tb_dlist_insert(dlist, i, 6);
	tb_dlist_insert(dlist, i, 7);
	tb_dlist_insert(dlist, i, 8);
	tb_dlist_insert(dlist, i, 9);
	tb_dlist_insert_head(dlist, 4);
	tb_dlist_insert_head(dlist, 3);
	tb_dlist_insert_head(dlist, 2);
	tb_dlist_insert_head(dlist, 1);
	tb_dlist_insert_head(dlist, 0);
	tb_dlist_insert_tail(dlist, 5);
	tb_dlist_insert_tail(dlist, 6);
	tb_dlist_insert_tail(dlist, 7);
	tb_dlist_insert_tail(dlist, 8);
	tb_dlist_insert_tail(dlist, 9);
	tb_dlist_int_dump(dlist);

	tb_trace("=============================================================");
	tb_trace("remove:");
	tb_dlist_nremove_head(dlist, 5);
	tb_dlist_nremove_last(dlist, 5);
	j = tb_dlist_remove(dlist, j);
	j = tb_dlist_remove(dlist, j);
	j = tb_dlist_remove(dlist, j);
	j = tb_dlist_remove(dlist, j);
	j = tb_dlist_remove(dlist, j);
	j = tb_dlist_remove(dlist, j);
	j = tb_dlist_remove(dlist, j);
	j = tb_dlist_remove(dlist, j);
	j = tb_dlist_remove(dlist, j);
	j = tb_dlist_remove(dlist, j);	
	tb_dlist_int_dump(dlist);

	tb_trace("=============================================================");
	tb_trace("replace:");
	tb_dlist_nreplace_head(dlist, 0xf, 10);
	tb_dlist_nreplace_last(dlist, 0xa, 10);
	tb_dlist_replace_head(dlist, 0);
	tb_dlist_replace_last(dlist, 0);
	tb_dlist_int_dump(dlist);

	tb_trace("=============================================================");
	tb_trace("clear:");
	tb_dlist_clear(dlist);
	tb_dlist_int_dump(dlist);

	tb_size_t score = 0;
	tb_trace("=============================================================");
	tb_trace("insert performance:");
	score += tb_dlist_insert_test();
	score += tb_dlist_insert_head_test();
	score += tb_dlist_insert_tail_test();
	score += tb_dlist_ninsert_test();
	score += tb_dlist_ninsert_head_test();
	score += tb_dlist_ninsert_tail_test();

	tb_trace("=============================================================");
	tb_trace("remove performance:");
	score += tb_dlist_remove_test();
	score += tb_dlist_remove_head_test();
	score += tb_dlist_remove_last_test();
	score += tb_dlist_nremove_test();
	score += tb_dlist_nremove_head_test();
	score += tb_dlist_nremove_last_test();

	tb_trace("=============================================================");
	tb_trace("replace performance:");
	score += tb_dlist_replace_test();
	score += tb_dlist_replace_head_test();
	score += tb_dlist_replace_last_test();
	score += tb_dlist_nreplace_test();
	score += tb_dlist_nreplace_head_test();
	score += tb_dlist_nreplace_last_test();

	tb_trace("=============================================================");
	tb_trace("iterator performance:");
	score += tb_dlist_iterator_next_test();
	score += tb_dlist_iterator_prev_test();

	tb_trace("=============================================================");
	tb_trace("score: %d", score / 100);

	getchar();
end:

	// exit dlist
	tb_dlist_exit(dlist);

	return 0;
}
