/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _INTERFACECOCINEROSERVIDORPEDIDOS_H_RPCGEN
#define _INTERFACECOCINEROSERVIDORPEDIDOS_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


#define CocineroPedidos 0x20000003
#define CocineroPedidos_version 1

#if defined(__STDC__) || defined(__cplusplus)
#define registrar_cocinero 1
extern  int * registrar_cocinero_1(int *, CLIENT *);
extern  int * registrar_cocinero_1_svc(int *, struct svc_req *);
#define notificar_pedido_terminado 2
extern  bool_t * notificar_pedido_terminado_1(int *, CLIENT *);
extern  bool_t * notificar_pedido_terminado_1_svc(int *, struct svc_req *);
extern int cocineropedidos_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define registrar_cocinero 1
extern  int * registrar_cocinero_1();
extern  int * registrar_cocinero_1_svc();
#define notificar_pedido_terminado 2
extern  bool_t * notificar_pedido_terminado_1();
extern  bool_t * notificar_pedido_terminado_1_svc();
extern int cocineropedidos_1_freeresult ();
#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_INTERFACECOCINEROSERVIDORPEDIDOS_H_RPCGEN */
