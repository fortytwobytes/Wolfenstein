OBJS    =       $(filter-out ../bin/main.o, $(wildcard ../bin/libc/*.o ../bin/srcs/*.o))

test:
	@for file in test_*.c; do \
		printf "\033[1;33m[testing]\t\t%s\033[0m\n" $$file; \
		gcc $$file $(OBJS) -o $$(basename $$file .c); \
		./$$(basename $$file .c); \
		if [ $$? -eq 0 ]; then \
			printf "\033[1;32m[test successful]\t%s\033[0m\n" $$(basename $$file .c); \
			printf "\033[1;32m**********************************\n\033[0m"; \
		else \
			printf "\033[1;31m[failure]\t%s\033[0m\n" $$(basename $$file .c); \
			printf "\033[1;31m**********************************\n\033[0m"; \
		fi; \
		printf "\n"; \
	done

