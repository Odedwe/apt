// -*- mode: cpp; mode: fold -*-
// Description								/*{{{*/
// $Id: cachefile.h,v 1.5 2002/04/27 04:28:04 jgg Exp $
/* ######################################################################
   
   CacheFile - Simple wrapper class for opening, generating and whatnot
   
   This class implements a simple 2 line mechanism to open various sorts
   of caches. It can operate as root, as not root, show progress and so on,
   it transparently handles everything necessary.
   
   This means it can rebuild caches from the source list and instantiates
   and prepares the standard policy mechanism.
   
   ##################################################################### */
									/*}}}*/
#ifndef PKGLIB_CACHEFILE_H
#define PKGLIB_CACHEFILE_H


#include <apt-pkg/depcache.h>
#include <apt-pkg/acquire.h>
#include <apt-pkg/sourcelist.h>

class pkgPolicy;
class pkgSourceList;
class pkgCacheFile
{
   protected:
   
   MMap *Map;
   pkgCache *Cache;
   pkgDepCache *DCache;
   pkgPolicy *Policy;
   pkgSourceList *SrcList;

   public:

   // We look pretty much exactly like a pointer to a dep cache
   inline operator pkgCache &() {return *Cache;};
   inline operator pkgCache *() {return Cache;};
   inline operator pkgDepCache &() {return *DCache;};
   inline operator pkgDepCache *() {return DCache;};
   inline operator pkgPolicy &() {return *Policy;};
   inline operator pkgPolicy *() {return Policy;};
   inline operator pkgSourceList &() {return *SrcList;};
   inline operator pkgSourceList *() {return SrcList;};
   inline pkgDepCache *operator ->() {return DCache;};
   inline pkgDepCache &operator *() {return *DCache;};
   inline pkgDepCache::StateCache &operator [](pkgCache::PkgIterator const &I) {return (*DCache)[I];};
   inline unsigned char &operator [](pkgCache::DepIterator const &I) {return (*DCache)[I];};

   bool BuildCaches(OpProgress *Progress = NULL,bool WithLock = true);
   __deprecated bool BuildCaches(OpProgress &Progress,bool const &WithLock = true) { return BuildCaches(&Progress, WithLock); };
   bool BuildSourceList(OpProgress *Progress = NULL);
   bool BuildPolicy(OpProgress *Progress = NULL);
   bool BuildDepCache(OpProgress *Progress = NULL);
   bool Open(OpProgress *Progress = NULL, bool WithLock = true);
   inline bool ReadOnlyOpen(OpProgress *Progress = NULL) { return Open(Progress, false); };
   __deprecated bool Open(OpProgress &Progress,bool const &WithLock = true) { return Open(&Progress, WithLock); };
   void Close();

   inline pkgCache* GetPkgCache() { BuildCaches(NULL, false); return Cache; };
   inline pkgDepCache* GetDepCache() { BuildDepCache(); return DCache; };
   inline pkgPolicy* GetPolicy() { BuildPolicy(); return Policy; };
   inline pkgSourceList* GetSourceList() { BuildSourceList(); return SrcList; };

   pkgCacheFile();
   virtual ~pkgCacheFile();
};

#endif
