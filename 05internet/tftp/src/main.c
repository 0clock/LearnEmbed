/*
 * Filename: 02tcpClint.c
 * Author: linus
 * Date: 2024-01-12
 * Version: 1.0
 *
 * Description: The purpose of this code.
 */

#include "header.h"
#include "menu.h"
#include "tftp.h"

int main(int argc, const char *argv[])
{
	print_menu();

	tftp_send();
	return 0;
}
