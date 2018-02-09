/*!The Treasure Box Library
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
 * Copyright (C) 2009 - 2018, TBOOX Open Source Group.
 *
 * @author      ruki
 * @file        aioo.c
 * @ingroup     platform
 */

/* //////////////////////////////////////////////////////////////////////////////////////
 * trace
 */
#define TB_TRACE_MODULE_NAME            "platform_aioo"
#define TB_TRACE_MODULE_DEBUG           (0)

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"
#include "../../asio/deprecated/aioe.h"

/* //////////////////////////////////////////////////////////////////////////////////////
 * declaration
 */
tb_long_t tb_aioo_rtor_wait(tb_socket_ref_t sock, tb_size_t code, tb_long_t timeout);

/* //////////////////////////////////////////////////////////////////////////////////////
 * implementation
 */
#if defined(TB_CONFIG_OS_WINDOWS)
#   include "../deprecated/aioo_select.c"
    tb_long_t tb_aioo_rtor_wait(tb_socket_ref_t sock, tb_size_t code, tb_long_t timeout)
    {
        return tb_aioo_rtor_select_wait(sock, code, timeout);
    }
#elif defined(TB_CONFIG_POSIX_HAVE_POLL)
#   include "../deprecated/aioo_poll.c"
    tb_long_t tb_aioo_rtor_wait(tb_socket_ref_t sock, tb_size_t code, tb_long_t timeout)
    {
        return tb_aioo_rtor_poll_wait(sock, code, timeout);
    }
#else
#   error have not available event mode
#endif

