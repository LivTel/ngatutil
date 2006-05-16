/*   
    Copyright 2006, Astrophysics Research Institute, Liverpool John Moores University.

    This file is part of NGATFITS.

    NGATFITS is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    NGATFITS is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with NGATFITS; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
/* ngat_util_FileUtilities.c -*- mode: Fundamental;-*-
** implementation of Java Class ngat.util.FileUtilities native interfaces
** $Header: /space/home/eng/cjm/cvs/ngatutil/c/ngat_util_FileUtilities.c,v 1.3 2006-05-16 18:56:57 cjm Exp $
*/
/**
 * ngat_util_FileUtilities.c contains all the native C routines corresponding to native methods in the Java
 * class ngat.util.FileUtilities.
 * @author Chris Mottram LJMU
 * @version $Revision: 1.3 $
 */
/**
 * This hash define is needed before including source files give us POSIX.4/IEEE1003.1b-1993 prototypes.
 */
#define _POSIX_SOURCE 1
/**
 * This hash define is needed before including source files give us POSIX.4/IEEE1003.1b-1993 prototypes.
 */
#define _POSIX_C_SOURCE 199309L
/**
 * This hash define is needed to make header files include X/Open UNIX entensions.
 * This allows us to use BSD/SVr4 function calls even when  _POSIX_C_SOURCE is defined.
 * This gets us prototypes of readlink/symlink/lstat under Linux.
 */
#define _XOPEN_SOURCE		(1)
/**
 * This hash define is needed to make header files include X/Open UNIX entensions.
 * This allows us to use BSD/SVr4 function calls even when  _POSIX_C_SOURCE is defined.
 * This gets us prototypes of readlink/symlink/lstat under Linux.
 */
#define _XOPEN_SOURCE_EXTENDED 	(1)
/**
 * This hash define is needed to make header files include BSD flavour definitions.
 * This allows us to use BSD function calls/defines even when  _POSIX_C_SOURCE is defined.
 * This gets us prototypes of the S_ISLNK macro under Linux, which according to the lstat man pages
 * is POSIX, but according to &lt;sys/stat.h&gt; is BSD.
 */
#define _BSD_SOURCE		(1)

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <jni.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "ngat_util_FileUtilities.h"

/* --------------------------------------------------------- */
/* hash defines */
/* --------------------------------------------------------- */
/**
 * TRUE is the value usually returned from routines to indicate success.
 */
#ifndef TRUE
#define TRUE 1
#endif
/**
 * FALSE is the value usually returned from routines to indicate failure.
 */
#ifndef FALSE
#define FALSE 0
#endif
/**
 * Constant value for the size of buffer to use for the error string.
 * @see #File_utilites_Error_String
 */
#define FILE_UTILITES_ERROR_STRING_LENGTH	(4096)

/* --------------------------------------------------------- */
/* internal variables */
/* --------------------------------------------------------- */
/**
 * Revision Control System identifier.
 */
static char rcsid[] = "$Id: ngat_util_FileUtilities.c,v 1.3 2006-05-16 18:56:57 cjm Exp $";
/**
 * Error string that holds any generated error messages.
 * @see #FILE_UTILITES_ERROR_STRING_LENGTH
 */
static char File_Utilities_Error_String[FILE_UTILITES_ERROR_STRING_LENGTH] = "";

/* --------------------------------------------------------- */
/* internal routines prototypes */
/* --------------------------------------------------------- */
static void FileUtilities_Throw_Exception_String(JNIEnv *env,char *function_name,int error_number,char *error_string);
/* --------------------------------------------------------- */
/* external routines */
/* --------------------------------------------------------- */
/**
 * Class:     ngat_util_FileUtilities<br>
 * Method:    readlink<br>
 * Signature: (Ljava/lang/String;I)Ljava/lang/String;<br>
 * Java Native Interface routine to read what a symbolic links points to (contains).
 * Uses readlink. readlink conforms to X/OPEN,4.4BSD.
 */
JNIEXPORT jstring JNICALL Java_ngat_util_FileUtilities_readlink(JNIEnv *env, jclass cls, 
	jstring link_filename,jint buffer_length)
{
	jstring return_string = NULL;
	const char *clink_filename = NULL;
	char *buff = NULL;
	int retval,readlink_errno;

/* convert link_filename jstring to C char* clink_filename */
	if(link_filename != NULL)
		clink_filename = (*env)->GetStringUTFChars(env,link_filename,0);
/* allocate buffer space for returned link contents, of length buffer_length */
	buff = (char*)malloc(buffer_length*sizeof(char));
	if(buff == NULL)
	{
		if(link_filename != NULL)
			(*env)->ReleaseStringUTFChars(env,link_filename,clink_filename);
		sprintf(File_Utilities_Error_String,"malloc(%ld) returned NULL.",buffer_length*sizeof(char));
		FileUtilities_Throw_Exception_String(env,"readlink",0,File_Utilities_Error_String);
		return (jstring)NULL;
	}
/* read link contents of filename clink_filename into buff */
	retval = readlink(clink_filename,buff,(size_t)buffer_length);
	if(retval < 0)
	{
		readlink_errno = errno;
		if(link_filename != NULL)
			(*env)->ReleaseStringUTFChars(env,link_filename,clink_filename);
		if(buff != NULL)
			free(buff);
		sprintf(File_Utilities_Error_String,"readlink(%s,%d) failed.",clink_filename,(int)buffer_length);
		FileUtilities_Throw_Exception_String(env,"readlink",readlink_errno,File_Utilities_Error_String);
		return (jstring)NULL;
	}
/* retval is the number of bytes in buff. Ensure buffer was not filled. */
	if(retval == buffer_length)
	{
		if(link_filename != NULL)
			(*env)->ReleaseStringUTFChars(env,link_filename,clink_filename);
		if(buff != NULL)
			free(buff);
		sprintf(File_Utilities_Error_String,"readlink(%s,%d):buffer full.",clink_filename,(int)buffer_length);
		FileUtilities_Throw_Exception_String(env,"readlink",0,File_Utilities_Error_String);
		return (jstring)NULL;
	}
/* buff is NOT NULL terminated by readlink. Terminate. */
	buff[retval] = '\0';
/* create return_string jstring from buff */
	return_string = (*env)->NewStringUTF(env,buff);
/* free link_filename */
	if(link_filename != NULL)
		(*env)->ReleaseStringUTFChars(env,link_filename,clink_filename);
/* free buff */
	if(buff != NULL)
		free(buff);
/* return return_string */
	return return_string;
}

/**
 * Class:     ngat_util_FileUtilities<br>
 * Method:    symlink<br>
 * Signature: (Ljava/lang/String;Ljava/lang/String;)V<br>
 * Java Native Interface routine to create a symbolic link.
 * Uses symlink. symlink conforms to SVr4, SVID, POSIX, BSD  4.3.
 */
JNIEXPORT void JNICALL Java_ngat_util_FileUtilities_symlink(JNIEnv *env,jclass cls,
	jstring link_contents,jstring link_filename)
{	
	const char *clink_filename = NULL;
	const char *clink_contents = NULL;
	int retval, symlink_errno;

/* convert link_contents jstring to C char* clink_contents */
	if(link_contents != NULL)
		clink_contents = (*env)->GetStringUTFChars(env,link_contents,0);
/* convert link_filename jstring to C char* clink_filename */
	if(link_filename != NULL)
		clink_filename = (*env)->GetStringUTFChars(env,link_filename,0);
/* create symbolic link clink_filename which points to (contains) clink_contents */
	retval = symlink(clink_contents,clink_filename);
	if(retval < 0)
	{
		symlink_errno = errno;
		if(link_filename != NULL)
			(*env)->ReleaseStringUTFChars(env,link_filename,clink_filename);
		if(link_contents != NULL)
			(*env)->ReleaseStringUTFChars(env,link_contents,clink_contents);
		sprintf(File_Utilities_Error_String,"symlink(%s,%s) failed.",clink_contents,clink_filename);
		FileUtilities_Throw_Exception_String(env,"symlink",symlink_errno,File_Utilities_Error_String);
		return;
	}
/* free link_filename */
	if(link_filename != NULL)
		(*env)->ReleaseStringUTFChars(env,link_filename,clink_filename);
/* free link_contents */
	if(link_contents != NULL)
		(*env)->ReleaseStringUTFChars(env,link_contents,clink_contents);
}

/**
 * Class:     ngat_util_FileUtilities<br>
 * Method:    symlink_lstat_exists<br>
 * Signature: (Ljava/lang/String;)Z<br>
 * Java Native Interface routine to test whether a symbolic link exists.
 * Uses lstat, and the macro S_ISLNK, which tests whether st_mode has the S_IFLNK bit set.
 * lstat conforms to 4.3BSD and SVr4.
 */
JNIEXPORT jboolean JNICALL Java_ngat_util_FileUtilities_symlink_1lstat_1exists(JNIEnv *env,jclass cls,
	jstring link_filename)
{
	struct stat link_stat;
	const char *clink_filename = NULL;
	int retval;
	int exists = FALSE;

/* convert link_filename jstring to C char* clink_filename */
	if(link_filename != NULL)
		clink_filename = (*env)->GetStringUTFChars(env,link_filename,0);
/* call lstat */
	retval = lstat(clink_filename,&link_stat);
	if(retval < 0)
	{
	/* An error has occured. This could be because the file does not exist.
	** Just return FALSE. */
		if(link_filename != NULL)
			(*env)->ReleaseStringUTFChars(env,link_filename,clink_filename);
		return FALSE;
	}
/* Does the mode say it is a link? */
	exists = S_ISLNK(link_stat.st_mode);
/* free link_filename */
	if(link_filename != NULL)
		(*env)->ReleaseStringUTFChars(env,link_filename,clink_filename);
/* return whether it is a link or not */
	return (jboolean)exists;
}

/* --------------------------------------------------------- */
/* internal routines */
/* --------------------------------------------------------- */
/**
 * This routine throws an exception of class ngat/util/FileUtilitiesNativeException. This is used to report
 * file utility error messages back to the Java layer.
 * @param env The JNI environment pointer.
 * @param function_name The name of the function in which this exception is being generated for.
 * @param error_number An error number to pass to the constructor of the exception, usually from errno.
 * @param error_string The string to pass to the constructor of the exception.
 */
static void FileUtilities_Throw_Exception_String(JNIEnv *env,char *function_name,int error_number,char *error_string)
{
	jclass exception_class = NULL;
	jobject exception_instance = NULL;
	jstring error_jstring = NULL;
	jstring function_name_jstring = NULL;
	jmethodID mid;
	int retval;

	exception_class = (*env)->FindClass(env,"ngat/util/FileUtilitiesNativeException");
	if(exception_class == NULL)
	{
		fprintf(stderr,"FileUtilities_Throw_Exception_String:FindClass failed:%s:(%d) %s\n",function_name,
			error_number,error_string);
		return;
	}
/* get FileUtilitiesNativeException constructor */
	mid = (*env)->GetMethodID(env,exception_class,"<init>","(Ljava/lang/String;ILjava/lang/String;)V");
	if(mid == 0)
	{
		/* One of the following exceptions has been thrown:
		** NoSuchMethodError, ExceptionInInitializerError, OutOfMemoryError */
		fprintf(stderr,"FileUtilities_Throw_Exception_String:GetMethodID failed:%s:(%d) %s\n",
			function_name,error_number,error_string);
		return;
	}
/* convert error_string to JString */
	error_jstring = (*env)->NewStringUTF(env,error_string);
	function_name_jstring = (*env)->NewStringUTF(env,function_name);
/* call constructor */
	exception_instance = (*env)->NewObject(env,exception_class,mid,function_name_jstring,
		(jint)error_number,error_jstring);
	if(exception_instance == NULL)
	{
		/* One of the following exceptions has been thrown:
		** InstantiationException, OutOfMemoryError */
		fprintf(stderr,"FileUtilities_Throw_Exception_String:NewObject failed %s:(%d) %s\n",
			function_name,error_number,error_string);
		return;
	}
/* throw instance */
	retval = (*env)->Throw(env,(jthrowable)exception_instance);
	if(retval !=0)
	{
		fprintf(stderr,"FileUtilities_Throw_Exception_String:Throw failed %d:%s:(%d) %s\n",retval,
			function_name,error_number,error_string);
	}
}

/*
** $Log: not supported by cvs2svn $
** Revision 1.2  2001/07/31 10:19:27  cjm
** Renamed FileUtilites to FileUtilities.
**
** Revision 1.1  2001/07/31 10:00:58  cjm
** Initial revision
**
** Revision 1.1  2001/06/20 15:56:16  cjm
** Initial revision
**
*/
