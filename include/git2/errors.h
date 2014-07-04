/*
 * Copyright (C) the libgit2 contributors. All rights reserved.
 *
 * This file is part of libgit2, distributed under the GNU GPL v2 with
 * a Linking Exception. For full terms see the included COPYING file.
 */
#ifndef INCLUDE_git_errors_h__
#define INCLUDE_git_errors_h__

#include "common.h"

/**
 * @file git2/errors.h
 * @brief Git error handling routines and variables
 * @ingroup Git
 * @{
 */
GIT_BEGIN_DECL

/** Generic return codes */
typedef enum {
	GIT_OK         =  0,		/**< No error */

	GIT_ERROR      = -1,		/**< Generic error */
	GIT_ENOTFOUND  = -3,		/**< Requested object could not be found */
	GIT_EEXISTS    = -4,		/**< Object exists preventing operation */
	GIT_EAMBIGUOUS = -5,		/**< More than one object matches */
	GIT_EBUFS      = -6,		/**< Output buffer too short to hold data */

	/* GIT_EUSER is a special error that is never generated by libgit2
	 * code.  You can return it from a callback (e.g to stop an iteration)
	 * to know that it was generated by the callback and not by libgit2.
	 */
	GIT_EUSER      = -7,

	GIT_EBAREREPO       =  -8,	/**< Operation not allowed on bare repository */
	GIT_EUNBORNBRANCH   =  -9,	/**< HEAD refers to branch with no commits */
	GIT_EUNMERGED       = -10,	/**< Merge in progress prevented operation */
	GIT_ENONFASTFORWARD = -11,	/**< Reference was not fast-forwardable */
	GIT_EINVALIDSPEC    = -12,	/**< Name/ref spec was not in a valid format */
	GIT_EMERGECONFLICT  = -13,	/**< Merge conflicts prevented operation */
	GIT_ELOCKED         = -14,	/**< Lock file prevented operation */
	GIT_EMODIFIED       = -15,	/**< Reference value does not match expected */
	GIT_ECERTIFICATE    = -16,      /**< Server certificate is invalid */

	GIT_PASSTHROUGH     = -30,	/**< Internal only */
	GIT_ITEROVER        = -31,	/**< Signals end of iteration with iterator */
} git_error_code;

/**
 * Structure to store extra details of the last error that occurred.
 *
 * This is kept on a per-thread basis if GIT_THREADS was defined when the
 * library was build, otherwise one is kept globally for the library
 */
typedef struct {
	char *message;
	int klass;
} git_error;

/** Error classes */
typedef enum {
	GITERR_NONE = 0,
	GITERR_NOMEMORY,
	GITERR_OS,
	GITERR_INVALID,
	GITERR_REFERENCE,
	GITERR_ZLIB,
	GITERR_REPOSITORY,
	GITERR_CONFIG,
	GITERR_REGEX,
	GITERR_ODB,
	GITERR_INDEX,
	GITERR_OBJECT,
	GITERR_NET,
	GITERR_TAG,
	GITERR_TREE,
	GITERR_INDEXER,
	GITERR_SSL,
	GITERR_SUBMODULE,
	GITERR_THREAD,
	GITERR_STASH,
	GITERR_CHECKOUT,
	GITERR_FETCHHEAD,
	GITERR_MERGE,
	GITERR_SSH,
	GITERR_FILTER,
	GITERR_REVERT,
	GITERR_CALLBACK,
	GITERR_CHERRYPICK,
} git_error_t;

/**
 * Return the last `git_error` object that was generated for the
 * current thread or NULL if no error has occurred.
 *
 * @return A git_error object.
 */
GIT_EXTERN(const git_error *) giterr_last(void);

/**
 * Clear the last library error that occurred for this thread.
 */
GIT_EXTERN(void) giterr_clear(void);

/**
 * Get the last error data and clear it.
 *
 * This copies the last error into the given `git_error` struct
 * and returns 0 if the copy was successful, leaving the error
 * cleared as if `giterr_clear` had been called.
 *
 * If there was no existing error in the library, -1 will be returned
 * and the contents of `cpy` will be left unmodified.
 */
GIT_EXTERN(int) giterr_detach(git_error *cpy);

/**
 * Set the error message string for this thread.
 *
 * This function is public so that custom ODB backends and the like can
 * relay an error message through libgit2.  Most regular users of libgit2
 * will never need to call this function -- actually, calling it in most
 * circumstances (for example, calling from within a callback function)
 * will just end up having the value overwritten by libgit2 internals.
 *
 * This error message is stored in thread-local storage and only applies
 * to the particular thread that this libgit2 call is made from.
 *
 * NOTE: Passing the `error_class` as GITERR_OS has a special behavior: we
 * attempt to append the system default error message for the last OS error
 * that occurred and then clear the last error.  The specific implementation
 * of looking up and clearing this last OS error will vary by platform.
 *
 * @param error_class One of the `git_error_t` enum above describing the
 *                    general subsystem that is responsible for the error.
 * @param string The formatted error message to keep
 */
GIT_EXTERN(void) giterr_set_str(int error_class, const char *string);

/**
 * Set the error message to a special value for memory allocation failure.
 *
 * The normal `giterr_set_str()` function attempts to `strdup()` the string
 * that is passed in.  This is not a good idea when the error in question
 * is a memory allocation failure.  That circumstance has a special setter
 * function that sets the error string to a known and statically allocated
 * internal value.
 */
GIT_EXTERN(void) giterr_set_oom(void);

/** @} */
GIT_END_DECL
#endif
