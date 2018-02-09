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
 * @file        sockdata_iocp.h
 * @ingroup     platform
 *
 */
#ifndef TB_PLATFORM_WINDOWS_SOCKDATA_IOCP_H
#define TB_PLATFORM_WINDOWS_SOCKDATA_IOCP_H

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"
#include "../sockdata.h"

/* //////////////////////////////////////////////////////////////////////////////////////
 * extern
 */
__tb_extern_c_enter__

/* //////////////////////////////////////////////////////////////////////////////////////
 * types
 */

// the iocp socket data type
typedef struct __tb_sockdata_iocp_t
{
    // the socket data (sock => priv)
    tb_cpointer_t*          data;

    // the socket data maximum count
    tb_size_t               maxn;
    
}tb_sockdata_iocp_t, *tb_sockdata_iocp_ref_t;

/* //////////////////////////////////////////////////////////////////////////////////////
 * interfaces
 */

/* //////////////////////////////////////////////////////////////////////////////////////
 * extern
 */
__tb_extern_c_leave__

#endif
