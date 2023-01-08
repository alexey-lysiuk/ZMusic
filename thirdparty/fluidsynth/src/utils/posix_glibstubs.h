#ifndef _GLIBSTUBS_H
#define _GLIBSTUBS_H

#include <assert.h>
#include <pthread.h>

/* Miscellaneous stubs */
#define GLIB_CHECK_VERSION(x, y, z) 1 /* Evaluate to 1 to get FluidSynth to use the "new" thread API */
#define GLIB_MAJOR_VERSION 2
#define GLIB_MINOR_VERSION 74

typedef struct
{
	int code;
	const char *message;
} GError;
typedef void *gpointer;
typedef int gboolean;

#define g_new(s, c) FLUID_ARRAY(s, c)
#define g_free(p) FLUID_FREE(p)
#define g_strfreev FLUID_FREE
#define g_newa(_type, _len) (_type *)_alloca(sizeof(_type) * (_len))
#define g_assert(a) assert(a)
#define G_LIKELY(expr) (expr)
#define G_UNLIKELY(expr) (expr)
#endif

#define g_return_val_if_fail(expr, val) if (expr) {} else { return val; }
#define g_clear_error(err) do {} while (0)

#define G_FILE_TEST_EXISTS 1
#define G_FILE_TEST_IS_REGULAR 2

#define g_file_test fluid_g_file_test
//#define g_shell_parse_argv fluid_g_shell_parse_argv
gboolean fluid_g_file_test(const char *path, int flags);
//gboolean fluid_g_shell_parse_argv(const char *command_line, int *argcp, char ***argvp, void *dummy);

#define g_get_monotonic_time fluid_g_get_monotonic_time
double fluid_g_get_monotonic_time(void);

/* Byte ordering */
#ifdef __BYTE_ORDER__
#define G_BYTE_ORDER __BYTE_ORDER__
#define G_BIG_ENDIAN __ORDER_BIG_ENDIAN__
#else
// If __BYTE_ORDER__ isn't defined, assume little endian
#define G_BYTE_ORDER 1234
#define G_BIG_ENDIAN 4321
#endif

#if G_BYTE_ORDER == G_BIG_ENDIAN
#define GINT16_FROM_LE(x) (int16_t)(((uint16_t)(x) >> 8) | ((uint16_t)(x) << 8))
#define GINT32_FROM_LE(x) (int32_t)((FLUID_LE16TOH(x) << 16) | (FLUID16_LE16TOH(x >> 16)))
#else
#define GINT32_FROM_LE(x) (x)
#define GINT16_FROM_LE(x) (x)

/* Thread support */
#define g_thread_supported() 1
#define g_thread_init(_) do {} while (0)
#define g_usleep usleep

typedef gpointer (*GThreadFunc)(void *data);
typedef struct
{
	GThreadFunc func;
	void *data;
	pthread_t *handle;
} GThread;

#define g_thread_create fluid_g_thread_create
#define g_thread_join fluid_g_thread_join
GThread *fluid_g_thread_create(GThreadFunc func, void *data, gboolean joinable, GError **error);
void fluid_g_thread_join(GThread *thread);

typedef pthread_mutex_t GMutex;
void g_mutex_init(GMutex* mutex);
void g_mutex_clear(GMutex* mutex);

typedef pthread_mutex_t GRecMutex;

typedef pthread_cond_t GCond;
void g_cond_init(GCond* cond);
void g_cond_clear(GCond* cond);

typedef pthread_key_t GPrivate;

typedef struct stat GStatBuf;



#endif
