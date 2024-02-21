cmake_minimum_required(VERSION 3.5)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wno-unused-result" CACHE STRING "Set C++ Compiler Flags" FORCE)

project (pidp11)

set(BLINKENLIGHT_COMMON_DIR ${PROJECT_SOURCE_DIR}/src/00_common)
set(BLINKENLIGHT_API_DIR ${PROJECT_SOURCE_DIR}/src/07.0_blinkenlight_api)
set(SIM_SOURCES_DIR ${PROJECT_SOURCE_DIR}/src/02.3_simh/4.x+realcons/src)
set(PDP11_SOURCES_DIR ${SIM_SOURCES_DIR}/PDP11)
set(REALCONS_DIR ${SIM_SOURCES_DIR}/REALCONS)

set(BLINKENLIGHT_API_SOURCES
    ${BLINKENLIGHT_API_DIR}/blinkenlight_panels.c
    ${BLINKENLIGHT_API_DIR}/blinkenlight_api_server_procs.c
    ${BLINKENLIGHT_API_DIR}/rpcgen_linux/rpc_blinkenlight_api_svc.c
    ${BLINKENLIGHT_API_DIR}/rpcgen_linux/rpc_blinkenlight_api_xdr.c
    ${BLINKENLIGHT_API_DIR}/historybuffer.c
    ${BLINKENLIGHT_COMMON_DIR}/bitcalc.c
    ${BLINKENLIGHT_COMMON_DIR}/radix.c
    ${BLINKENLIGHT_COMMON_DIR}/mcout.c
    ${BLINKENLIGHT_COMMON_DIR}/errno2txt.c
)

set(DISPLAY_SOURCES
    ${SIM_SOURCES_DIR}/display/display.c
    ${SIM_SOURCES_DIR}/display/sim_ws.c
    ${SIM_SOURCES_DIR}/display/vt11.c
)

set(PDP11_SOURCES 
    ${PDP11_SOURCES_DIR}/pdp11_fp.c 
    ${PDP11_SOURCES_DIR}/pdp11_cpu.c
    ${PDP11_SOURCES_DIR}/pdp11_dz.c
    ${PDP11_SOURCES_DIR}/pdp11_cis.c
    ${PDP11_SOURCES_DIR}/pdp11_lp.c
    ${PDP11_SOURCES_DIR}/pdp11_rk.c
    ${PDP11_SOURCES_DIR}/pdp11_rl.c
    ${PDP11_SOURCES_DIR}/pdp11_rp.c
    ${PDP11_SOURCES_DIR}/pdp11_rx.c
    ${PDP11_SOURCES_DIR}/pdp11_stddev.c 
    ${PDP11_SOURCES_DIR}/pdp11_sys.c
    ${PDP11_SOURCES_DIR}/pdp11_tc.c
    ${PDP11_SOURCES_DIR}/pdp11_tm.c
    ${PDP11_SOURCES_DIR}/pdp11_ts.c
    ${PDP11_SOURCES_DIR}/pdp11_io.c
    ${PDP11_SOURCES_DIR}/pdp11_rq.c
    ${PDP11_SOURCES_DIR}/pdp11_tq.c
    ${PDP11_SOURCES_DIR}/pdp11_pclk.c
	${PDP11_SOURCES_DIR}/pdp11_ry.c
    ${PDP11_SOURCES_DIR}/pdp11_pt.c
    ${PDP11_SOURCES_DIR}/pdp11_hk.c
    ${PDP11_SOURCES_DIR}/pdp11_xq.c
    ${PDP11_SOURCES_DIR}/pdp11_xu.c
    ${PDP11_SOURCES_DIR}/pdp11_vh.c
    ${PDP11_SOURCES_DIR}/pdp11_rh.c
    ${PDP11_SOURCES_DIR}/pdp11_tu.c
    ${PDP11_SOURCES_DIR}/pdp11_cpumod.c
    ${PDP11_SOURCES_DIR}/pdp11_cr.c
    ${PDP11_SOURCES_DIR}/pdp11_rf.c
    ${PDP11_SOURCES_DIR}/pdp11_dl.c
    ${PDP11_SOURCES_DIR}/pdp11_ta.c
    ${PDP11_SOURCES_DIR}/pdp11_rc.c
    ${PDP11_SOURCES_DIR}/pdp11_kg.c
    ${PDP11_SOURCES_DIR}/pdp11_ke.c
    ${PDP11_SOURCES_DIR}/pdp11_dc.c
    ${PDP11_SOURCES_DIR}/pdp11_dmc.c
    ${PDP11_SOURCES_DIR}/pdp11_kmc.c 
    ${PDP11_SOURCES_DIR}/pdp11_dup.c
    ${PDP11_SOURCES_DIR}/pdp11_rs.c
    ${PDP11_SOURCES_DIR}/pdp11_vt.c
    ${PDP11_SOURCES_DIR}/pdp11_td.c
    ${PDP11_SOURCES_DIR}/pdp11_io_lib.c
    # ${DISPLAY_SOURCES}
)

set(SIM_SOURCES
    ${SIM_SOURCES_DIR}/scp.c
    ${SIM_SOURCES_DIR}/sim_console.c
    ${SIM_SOURCES_DIR}/sim_fio.c
    ${SIM_SOURCES_DIR}/sim_timer.c
    ${SIM_SOURCES_DIR}/sim_sock.c
    ${SIM_SOURCES_DIR}/sim_tmxr.c
    ${SIM_SOURCES_DIR}/sim_ether.c
    ${SIM_SOURCES_DIR}/sim_tape.c
    ${SIM_SOURCES_DIR}/sim_disk.c
    ${SIM_SOURCES_DIR}/sim_serial.c
    ${SIM_SOURCES_DIR}/sim_video.c
    ${SIM_SOURCES_DIR}/sim_imd.c
)

set(REALCONS_SOURCES
    ${REALCONS_DIR}/realcons.c
    ${REALCONS_DIR}/realcons_simh.c
    ${BLINKENLIGHT_API_DIR}/blinkenlight_api_client.c
    ${BLINKENLIGHT_API_DIR}/rpcgen_linux/rpc_blinkenlight_api_clnt.c
    ${BLINKENLIGHT_API_DIR}/rpcgen_linux/rpc_blinkenlight_api_xdr.c
    ${BLINKENLIGHT_API_DIR}/blinkenlight_panels.c
    ${BLINKENLIGHT_COMMON_DIR}/bitcalc.c
    ${REALCONS_DIR}/realcons_console_pdp11_20.c
    ${REALCONS_DIR}/realcons_console_pdp11_40.c
    ${REALCONS_DIR}/realcons_console_pdp11_70.c
)

set(SERVER11_SOURCES
    src/11_pidp_server/pidp11/main.c
    src/11_pidp_server/pidp11/gpio.c
    src/11_pidp_server/pidp11/gpiopattern.c	
	src/11_pidp_server/pidp11/print.c
    ${BLINKENLIGHT_API_SOURCES}
)
add_executable(server11 ${SERVER11_SOURCES})

target_compile_definitions(server11
    PRIVATE
        BLINKENLIGHT_SERVER
)

target_include_directories(server11
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/src/11_pidp_server/pidp11
        ${BLINKENLIGHT_COMMON_DIR}
        ${BLINKENLIGHT_API_DIR}
        ${BLINKENLIGHT_API_DIR}/rpcgen_linux
        /usr/include/tirpc
)

target_link_libraries(server11
    PRIVATE
        pthread
        tirpc
)

set(CLIENT11_SOURCES
    ${REALCONS_SOURCES}
    ${SIM_SOURCES}
    ${PDP11_SOURCES}
)
add_executable(client11 ${CLIENT11_SOURCES})

target_compile_definitions(client11
    PUBLIC 
        USE_REALCONS
    PRIVATE
        _GNU_SOURCE
        __STRICT_ANSI__
        BLINKENLIGHT_CLIENT
        USE_REALCONS
        VM_PDP11
        USE_NETWORK
        HAVE_PCAP_NETWORK
        HAVE_TAP_NETWORK
)

target_include_directories(client11
    PRIVATE 
        ${SIM_SOURCES_DIR}
        ${REALCONS_DIR}
        ${BLINKENLIGHT_COMMON_DIR}
        ${BLINKENLIGHT_API_DIR}
        ${BLINKENLIGHT_API_DIR}/rpcgen_linux
        /usr/include/tirpc
)

target_link_libraries(client11
    PRIVATE
        pthread
        m
        dl
        readline
        tirpc
        pcap
)

set(SCANSW_SOURCES 
    ${PROJECT_SOURCE_DIR}/src/11_pidp_server/scanswitch/scansw.c
)
add_executable(scansw ${SCANSW_SOURCES})
