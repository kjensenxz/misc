#!/usr/bin/sh
# kexec.sh - load bzImage and initrd using kexec with user-specified or
# existing boot cmdline.

PROG=$0

# $1: optional exit code
function usage() {
	>&2 echo "usage: ${PROG} bzImage initrd ['cmdline']";

	if [ -n $1 ]; then
		>&2 echo "exiting with $(( $1 ))";
		exit $(( $1 ));
	fi

	exit 0 # EX_OK // successful termination;
}

# $@: quit message
function quit() {
	>&2 printf "$@";
	usage 64 # EX_USAGE // command line usage error
}

# $1: kexec str
function __do_kexec() {
	echo "doing kexec ${1}..."; >&2
	kexec ${1};
	RETVAL=$?
	echo "done. kexec returned $RETVAL" >&2

	if [ $(( RETVAL )) -eq 0 ]; then
		echo "kernel will load on next reboot." >&2
	fi;

	return $RETVAL
}

declare KERNEL=$1
declare INITRD=$2
declare CMDLINE=$3
declare ERRMSG=""

# just a little sanity checking...
# make sure user specified kernel and initrd.
# additionally, make sure the kernel appears valid 
# and check if initramfs is a valid file.
# use /proc/cmdline if user did not specify cmdline.
# if /proc/cmdline is unavailable, the user must specify it.
if [ -z "${KERNEL}" ]; then
	ERRMSG+="error: no kernel specified.\n";
else
	if [[ ! $(file "${KERNEL}") =~ 'bzImage' ]]; then
		ERRMSG+="error: kernel '${KERNEL}' does not appear to be a valid bzImage.\n";
	fi; if [ ! -x "${KERNEL}" ]; then
		ERRMSG+="error: kernel '${KERNEL}' is not marked executable.\n";
	fi; if [ ! -r "${KERNEL}" ]; then
		ERRMSG+="error: kernel '${KERNEL}' is not marked readable.\n";
        fi;
fi; if [ -z "${INITRD}" ]; then
	ERRMSG+="error: no initrd specified.\n";
else
	if [ ! -r "${INITRD}" ]; then
		ERRMSG+="error: initrd '${INITRD}' is not marked readable.\n";
	fi;
fi; if [[ -z "${CMDLINE}" && -r /proc/cmdline ]]; then
	CMDLINE=$(cat /proc/cmdline);
else
	ERRMSG+="error: no command line specified; /proc/cmdline is unreadable.\n";
fi; 
# if we have errors, print them, give user correct usage, & exit 1.
if [ -n "${ERRMSG}" ]; then
	quit "${ERRMSG}";
fi
# otherwise, we can continue


_KPARAM="--load ${KERNEL} --initrd=${INITRD} --command-line=\"${CMDLINE}\"";

printf "\n\nkexec ${_KPARAM}\n\n" >&2
printf 'are you sure you want to do this? [Y/n]: ' >&2

while read CONFRM; do
	case "${CONFRM}" in
		Y*)
			__do_kexec "${_KPARAM}"
			exit $?;
			;;
		y*)
			printf 'please answer Y or n. ' >&2;
			;;
		*)
			break
			;;
	esac;
done;

unset CONFRM _KPARAM KERNEL INITRD CMDLINE PROG # reduce pollution
exit 75; # EX_TEMPFAIL // temp failure; user is invited to retry
