/*-------------------------------------------------------------------------
 *
 * nodemgr.h
 *  Routines for node management
 *
 *
 * Portions Copyright (c) 1996-2011, PostgreSQL Global Development Group
 * Portions Copyright (c) 2010-2012, Postgres-XC Development Group
 * Portions Copyright (c) 2014-2017, ADB Development Group
 *
 * IDENTIFICATION
 * 		src/include/pgxc/nodemgr.h
 *
 *-------------------------------------------------------------------------
 */
#ifndef NODEMGR_H
#define NODEMGR_H

#include "nodes/parsenodes.h"

#define PGXC_NODENAME_LENGTH	64

/* GUC parameters, limit for number of nodes */
extern int 	MaxDataNodes;
extern int 	MaxCoords;
/* Global number of nodes */
extern volatile int NumDataNodes;
extern volatile int NumCoords;
extern volatile int NumCnNodes;
extern volatile int NumDnNodes;
/* Node definition */
typedef struct
{
	Oid 		nodeoid;
	NameData	nodename;
	NameData	nodehost;
	int			nodeport;
	bool		nodeisprimary;
	bool 		nodeispreferred;
} NodeDefinition;

extern void NodeTablesShmemInit(void);
extern Size NodeTablesShmemSize(void);

extern void PgxcNodeListAndCount(void);
extern void PgxcNodeGetOids(Oid **coOids, Oid **dnOids,
							int *num_coords, int *num_dns,
							bool update_preferred);
extern NodeDefinition *PgxcNodeGetDefinition(Oid node);
extern NodeDefinition *PgxcNodeGetAllDefinition(int *numCN, int *numDN);
extern void PgxcNodeAlter(AlterNodeStmt *stmt);
extern void PgxcNodeCreate(CreateNodeStmt *stmt);
extern void PgxcNodeRemove(DropNodeStmt *stmt);

#endif	/* NODEMGR_H */
