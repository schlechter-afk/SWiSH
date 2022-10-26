.PHONY: main
main:
	gcc -g cd.c execute.c echo.c main.c mainfunc.c pwd.c ls.c history.c pinfo.c discovery.c pipe.c fg.c fgjobs.c bgjobs.c sig.c jobs.c -o shell