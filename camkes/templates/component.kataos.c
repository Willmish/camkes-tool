/*#
 *# Copyright 2017, Data61
 *# Commonwealth Scientific and Industrial Research Organisation (CSIRO)
 *# ABN 41 687 119 230.
 *#
 *# This software may be distributed and modified according to the terms of
 *# the BSD 2-Clause license. Note that NO WARRANTY is provided.
 *# See "LICENSE_BSD2.txt" for details.
 *#
 *# @TAG(DATA61_BSD)
 #*/

/*#
 *# KataOS support.
 #*/

#include <autoconf.h>
#include <sel4camkes/gen_config.h>
#include <assert.h>
#include <sel4/types.h>
#include <sel4/sel4.h>
#include <sel4utils/mapping.h>

/*- macro next_pow2(val) -*/
    /*? pow(2, val.bit_length()) ?*/
/*- endmacro -*/

/*# TODO(sleffler): make more of these conditional? #*/
/*- set self_cnode = alloc_cap('cnode', my_cnode, write=true) -*/
const seL4_CPtr SELF_CNODE = /*? self_cnode ?*/;
/*- set self_pd = alloc_cap('pd', my_pd, write=true) -*/
const seL4_CPtr SELF_VSPACE_ROOT = /*? self_pd ?*/;
/*- set recv_cnode = alloc('recv_cnode', seL4_CapTableObject, size_bits=5) -*/
const seL4_CPtr MEMORY_RECV_CNODE = /*? recv_cnode ?*/;
const unsigned char MEMORY_RECV_CNODE_DEPTH = 5;

/*# Arrange to receive the BootInfo frame that comes with the UntypedMemory caps. #*/
/*- if configuration[me.name].get('untyped_memory', False) -*/
    /*# Setup a page for the loader to copy the BootInfo into #*/
    char bootinfo_frame[/*? 4096 ?*/]
    ALIGN(PAGE_SIZE_4K) SECTION("align_12bit");
    /*- do register_fill_frame('bootinfo_frame', 'CDL_FrameFill_BootInfo CDL_FrameFill_BootInfo_BootInfo', 4096) -*/
    /*- do my_cnode.__setattr__('has_untyped_memory', True) -*/
    /*- do my_cnode.__setattr__('headroom', my_cnode['headroom'] + 80) -*/
/*- endif -*/

/*- set cnode_headroom = configuration[me.address_space].get('cnode_headroom') -*/
/*- if cnode_headroom -*/
        /*- if isinstance(cnode_headroom, six.string_types) -*/
            /*- set headroom = int(cnode_headroom, 0) -*/
        /*- else -*/
            /*- set headroom = cnode_headroom -*/
        /*- endif -*/
    /*- do my_cnode.__setattr__('headroom', my_cnode['headroom'] + headroom) -*/
/*- endif -*/

/*# No cap allocation from here on! We assume all caps exist so we can guess our cnode size from the
 * holding slot #*/
/*- set holding_slot = alloc_cap('temporary_kataos_slot', None) -*/
const seL4_CPtr SELF_CNODE_FIRST_SLOT = /*? holding_slot ?*/;
/*- if cap_space.cnode.size_bits == 'auto' -*/
    /*- set size_bits = configuration[me.name].get('cnode_size_bits') -*/
    /*- if size_bits is not none -*/
        /*- set cnodesize = pow(2, size_bits) -*/
    /*- else -*/
        /*- set cnodesize = next_pow2(holding_slot + my_cnode['headroom']) -*/
    /*- endif -*/
/*- else -*/
    /*- set cnodesize = pow2(cap_space.cnode.size_bits) -*/
/*- endif -*/
const seL4_CPtr SELF_CNODE_LAST_SLOT = /*? cnodesize ?*/;
