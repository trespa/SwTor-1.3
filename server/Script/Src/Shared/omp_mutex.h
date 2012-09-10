//-----------------------------------------------------------------------------
// OpenMP runtime support library for Visual C++
// Copyright (C) Microsoft Corporation.  All rights reserved.
//-----------------------------------------------------------------------------

// OpenMP C/C++ Version 2.0

#pragma once

#ifndef OMP_MUTEX_H
#define OMP_MUTEX_H

#include <omp.h>


struct omp_mutex
{
	inline omp_mutex()
	{
		omp_init_lock(&lock);
	}
	inline ~omp_mutex()
	{
		omp_destroy_lock(&lock);
	}
	inline void set()
	{
		omp_set_lock(&lock);
	}
	inline void unset()
	{
		omp_unset_lock(&lock);
	}
private:
	omp_lock_t lock;

	omp_mutex(const omp_mutex&);
	void operator=(const omp_mutex&);
};


struct omp_scoped
{
	inline omp_scoped(omp_mutex& lock)
		: mutex(&lock), locked(0)
	{
		lock.set();
		locked = 1;
	}
	inline ~omp_scoped()
	{
		if(locked)
		{
			locked = 0;
			mutex->set();
		}
	}
private:
	omp_mutex* mutex;
	unsigned locked;		// protection from omp parallel

	omp_scoped(const omp_scoped&);
	void operator=(const omp_scoped&);
};


#endif