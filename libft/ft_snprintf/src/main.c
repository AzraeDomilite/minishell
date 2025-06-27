/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2004/05/20 19:09:54 by blucken           #+#    #+#             */
/*   Updated: 2025/05/04 19:24:16 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <string.h>
// #include <limits.h>
// #include "ft_snprintf.h"

// void	test_case(const char *format, ...)
// {
// 	char	buf1[100];
// 	char	buf2[100];
// 	int		ret1;
// 	int		ret2;
// 	va_list	args1;
// 	va_list	args2;
// 	va_list args_copy1;
// 	va_list args_copy2;

// 	va_start(args1, format);
// 	va_start(args2, format);
// 	va_copy(args_copy1, args1);
// 	va_copy(args_copy2, args2);
// 	memset(buf1, 'A', sizeof(buf1));
// 	memset(buf2, 'A', sizeof(buf2));
// 	ret1 = vsnprintf(buf1, sizeof(buf1), format, args_copy1);
// 	ret2 = ft_vsnprintf(buf2, sizeof(buf2), format, args_copy2);
// 	printf("Format: \"%s\"\n", format);
// 	printf("std  : [%d] \"%s\"\n", ret1, buf1);
// 	printf("ft   : [%d] \"%s\"\n", ret2, buf2);
// 	printf("Match: %s\n\n",
// 		(ret1 == ret2 && strcmp(buf1, buf2) == 0) ? "✓" : "✗");

// 	va_end(args_copy1);
// 	va_end(args_copy2);
// 	va_end(args1);
// 	va_end(args2);
// }

// void	test_edge_cases(void)
// {
// 	char	buffer[10];
// 	int		ret;

// 	printf("=== Edge Cases ===\n");
// 	ret = ft_snprintf(NULL, 0, "Testing null buffer");
// 	printf("NULL buffer, size 0: [%d]\n", ret);
// 	ret = ft_snprintf(buffer, sizeof(buffer),
// 		"This string is too long for the buffer");
// 	printf("Truncation: [%d] \"%s\"\n", ret, buffer);
// 	ret = ft_snprintf(buffer, sizeof(buffer), "");
// 	printf("Empty format: [%d] \"%s\"\n", ret, buffer);
// 	printf("\n");
// }

// int	main(void)
// {
// 	int		number;
// 	char	character;
// 	char	*string;
// 	void	*pointer;

// 	number = 42;
// 	character = 'X';
// 	string = "Hello, 42!";
// 	pointer = &number;
// 	printf("=== Basic Format Specifiers ===\n");
// 	test_case("Integer: %d", number);
// 	test_case("Character: %c", character);
// 	test_case("String: %s", string);
// 	test_case("Pointer: %p", pointer);
// 	test_case("Unsigned: %u", 4294967295u);
// 	test_case("Hex lower: %x", 255);
// 	test_case("Hex upper: %X", 255);
// 	test_case("Percent: %%");
// 	printf("=== Width and Precision ===\n");
// 	test_case("Width 10: '%10d'", 42);
// 	test_case("Precision 5: '%.5d'", 42);
// 	test_case("Width 10, Precision 5: '%10.5d'", 42);
// 	test_case("String precision 3: '%.3s'", "ABCDEF");
// 	printf("=== Flags ===\n");
// 	test_case("Left-aligned: '%-10d'", 42);
// 	test_case("Sign: '%+d'", 42);
// 	test_case("Space: '% d'", 42);
// 	test_case("Zero-padded: '%05d'", 42);
// 	test_case("Alternative form hex: '%#x'", 42);
// 	printf("=== Combining Specifiers ===\n");
// 	test_case("Combined: '%+10.5d'", 42);
// 	test_case("Negative: '%+10.5d'", -42);
// 	printf("=== Multiple Conversions ===\n");
// 	test_case("Multiple: '%d %s %c %x', %p", 42, "test", 'Z',
//		255, pointer);
// 	test_edge_cases();
// 	printf("=== Integer Limits ===\n");
// 	test_case("INT_MAX: %d", INT_MAX);
// 	test_case("INT_MIN: %d", INT_MIN);

// 	return (0);
// }
