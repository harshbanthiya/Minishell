#include "test.h"
#include "../includes/ms_execution.h"
#include "../includes/minishell.h"

t_shell	g_shell;

int main(){
	init_g_shell();

    TEST_SECTION("echo hello");
    {
		t_command *command = cmd_init_cmdinvo((const char**)ft_split("echo hello", ' '));

		int status = cmd_exec_commands(command);
		CHECK_EQ(status, 0);
		cmd_free_cmdinvo(command);
    }

    TEST_SECTION("cat /etc/passwd > output.txt");
    {
		t_command *command = cmd_init_cmdinvo((const char**)ft_split("cat /etc/passwd", ' '));
		cmd_add_outredirect(command, "output.txt", 1, false);

		int status = cmd_exec_commands(command);
		CHECK_EQ(status, 0);
		CHECK(system("diff --color -u /etc/passwd output.txt") == 0);
		cmd_free_cmdinvo(command);
		remove("output.txt");
    }

	TEST_SECTION("リダイレクト先が既に存在しているファイルの場合");
    {
		system("echo aaaaaaaaaaaaaaaaaaaaaaaaaaaaa > output.txt ; cp output.txt expected.txt ; echo hello > expected.txt");
		t_command *command = cmd_init_cmdinvo((const char**)ft_split("echo hello", ' '));
		cmd_add_outredirect(command, "output.txt", 1, false);

		int status = cmd_exec_commands(command);
		CHECK_EQ(status, 0);
		CHECK(system("diff --color -u expected.txt output.txt") == 0);
		cmd_free_cmdinvo(command);
		remove("output.txt");
    }

    TEST_SECTION("/usr/bin/cat /etc/passwd > output.txt");
    {
		t_command *command = cmd_init_cmdinvo((const char**)ft_split("/usr/bin/cat /etc/passwd", ' '));
		cmd_add_outredirect(command, "output.txt", 1, false);

		int status = cmd_exec_commands(command);
		CHECK_EQ(status, 0);
		CHECK(system("diff --color -u /etc/passwd output.txt") == 0);
		cmd_free_cmdinvo(command);
		remove("output.txt");
    }

    TEST_SECTION("echo abc > actual.txt ; echo def >> actual.txt  追記リダイレクト");
    {
		system("echo abc > actual.txt");
		t_command *command = cmd_init_cmdinvo((const char**)ft_split("echo def", ' '));
		cmd_add_outredirect(command, "actual.txt", 1, true);

		int status = cmd_exec_commands(command);
		CHECK_EQ(status, 0);
		CHECK(system("echo abc > expected.txt ; echo def >> expected.txt" " && "
				"diff --color -u expected.txt actual.txt") == 0);
		cmd_free_cmdinvo(command);
		remove("actual.txt");
		remove("expected.txt");
    }

    TEST_SECTION("cat < Makefile");
    {
		t_command *command = cmd_init_cmdinvo((const char**)ft_split("cat", ' '));
		cmd_add_inredirect(command, "Makefile", 0);

		int status = cmd_exec_commands(command);
		CHECK_EQ(status, 0);
		cmd_free_cmdinvo(command);
    }

    TEST_SECTION("/usr/bin/cat < Makefile");
    {
		t_command *command = cmd_init_cmdinvo((const char**)ft_split("/usr/bin/cat", ' '));
		cmd_add_inredirect(command, "Makefile", 0);

		int status = cmd_exec_commands(command);
		CHECK_EQ(status, 0);
		cmd_free_cmdinvo(command);
    }

    TEST_SECTION("cat < not_exists  存在しないファイルを入力リダイレクトするとエラー");
    {
		t_command *command = cmd_init_cmdinvo((const char**)ft_split("cat", ' '));
		cmd_add_inredirect(command, "not_exists", 0);

		int status = cmd_exec_commands(command);
		CHECK(status != 0);
		cmd_free_cmdinvo(command);
    }

    TEST_SECTION("cat < test.h > output.txt");
    {
		t_command *command = cmd_init_cmdinvo((const char**)ft_split("cat", ' '));
		cmd_add_inredirect(command, "test.h", 0);
		cmd_add_outredirect(command, "output.txt", 1, false);

		int status = cmd_exec_commands(command);
		CHECK_EQ(status, 0);
		CHECK(system("diff --color -u test.h output.txt") == 0);
		cmd_free_cmdinvo(command);
		remove("output.txt");
    }

    TEST_SECTION("cat Makefile > a > b  出力リダイレクトが複数");
    {
		t_command *command = cmd_init_cmdinvo((const char**)ft_split("cat Makefile", ' '));
		cmd_add_outredirect(command, "actual_a", 1, false);
		cmd_add_outredirect(command, "actual_b", 1, false);

		int status = cmd_exec_commands(command);
		CHECK_EQ(status, 0);
		CHECK(system("cat Makefile > expected_a > expected_b" " && "
			  "diff --color -u expected_a actual_a && diff --color -u expected_b actual_b") == 0);
		cmd_free_cmdinvo(command);
		remove("actual_a");
		remove("actual_b");
		remove("expected_a");
		remove("expected_b");
    }

    TEST_SECTION("cat < Makefile < test.h > output.txt  入力リダイレクトが複数");
    {
		t_command *command = cmd_init_cmdinvo((const char**)ft_split("cat", ' '));
		cmd_add_inredirect(command, "Makefile", 0);
		cmd_add_inredirect(command, "test.h", 0);
		cmd_add_outredirect(command, "output.txt", 1, false);

		int status = cmd_exec_commands(command);
		CHECK_EQ(status, 0);
		CHECK(system("cat < Makefile < test.h > expected.txt" " && "
			  "diff --color -u expected.txt output.txt") == 0);
		cmd_free_cmdinvo(command);
		remove("expected.txt");
		remove("output.txt");
    }

	TEST_SECTION("cat Makefile >> a >> b 追記リダイレクションの時は途中のファイルは上書きされない");
    {
		system("echo ThisIsA > actual_a ; echo ThisIsB > actual_b");
		t_command *command = cmd_init_cmdinvo((const char**)ft_split("cat Makefile", ' '));
		cmd_add_outredirect(command, "actual_a", 1, true);
		cmd_add_outredirect(command, "actual_b", 1, true);

		int status = cmd_exec_commands(command);
		CHECK_EQ(status, 0);
		system("echo ThisIsA > expected_a ; echo ThisIsB > expected_b");
		CHECK(system("cat Makefile >> expected_a >> expected_b" " && "
			  "diff --color -u expected_a actual_a && diff --color -u expected_b actual_b") == 0);
		cmd_free_cmdinvo(command);
		remove("actual_a");
		remove("actual_b");
		remove("expected_a");
		remove("expected_b");
    }

	TEST_SECTION("複数fd出力リダイレクション");
	{
		// 複数fd出力を行うプログラムを作成
		system("printf '#include<unistd.h>\nint main(){write(1, \"fd1\", 3);write(2, \"fd2\", 3);write(3, \"fd3\", 3);}' > multiple_fd_out.c && gcc multiple_fd_out.c -o multiple_fd_out");
		t_command *command = cmd_init_cmdinvo((const char **)ft_split("./multiple_fd_out", ' '));
		// ./a.out 3> file3 2> file2 1> file1; cat file3 file2 file1
		cmd_add_outredirect(command, "actual_3", 3, true);
		cmd_add_outredirect(command, "actual_2", 2, true);
		cmd_add_outredirect(command, "actual_1", 1, true);

		int status = cmd_exec_commands(command);
		CHECK_EQ(status, 0);
		system("./multiple_fd_out 3> expected_3 2> expected_2 1> expected_1");
		CHECK(system("diff --color -u expected_3 actual_3"
			  "&& diff --color -u expected_2 actual_2"
			  "&& diff --color -u expected_1 actual_1") == 0);
		cmd_free_cmdinvo(command);
		remove("actual_3");
		remove("actual_2");
		remove("actual_1");
		remove("expected_3");
		remove("expected_2");
		remove("expected_1");
		remove("multiple_fd_out.c");
		remove("multiple_fd_out");
	}

	TEST_SECTION("複数fd入力リダイレクション");
	{
		// 複数fd出力を行うプログラムを作成
		system("printf '#include<unistd.h>\nint main(){int size, buf[500]; size=read(0, buf, 100); write(1, buf, size); size=read(3, buf, 100); write(1, buf, size);}' > multiple_fd_in.c && gcc multiple_fd_in.c -o multiple_fd_in");
		t_command *command = cmd_init_cmdinvo((const char **)ft_split("./multiple_fd_in", ' '));
		system("echo this_is_hoge > hoge && echo this_is_fuga > fuga");
		// ./multiple_fd_in 0<hoge 3<fuga > actual
		cmd_add_inredirect(command, "hoge", 0);
		cmd_add_inredirect(command, "fuga", 3);
		cmd_add_outredirect(command, "actual", 1, true);

		int status = cmd_exec_commands(command);
		CHECK_EQ(status, 0);
		system("./multiple_fd_in 0<hoge 3<fuga > expected");
		CHECK(system("diff --color -u expected actual") == 0);
		cmd_free_cmdinvo(command);
		remove("actual");
		remove("expected");
		remove("multiple_fd_in.c");
		remove("multiple_fd_in");
		remove("hoge");
		remove("fuga");
	}

    TEST_SECTION("cat /etc/passwd | wc > output.txt  パイプが1つの場合");
    {
		t_command *first_command = cmd_init_cmdinvo((const char**)ft_split("cat /etc/passwd", ' '));

		t_command *second_command = cmd_init_cmdinvo((const char**)ft_split("wc", ' '));
		cmd_add_outredirect(second_command, "output.txt", 1, false);

		cmd_cmdinvo_add_pipcmd(&first_command, second_command);

		int status = cmd_exec_commands(first_command);
		CHECK_EQ(status, 0);
		CHECK(system("cat /etc/passwd | wc > expected.txt ; diff --color -u expected.txt output.txt") == 0);
		cmd_free_cmdinvo(first_command);
		remove("output.txt");
    }

    TEST_SECTION("cat /etc/passwd | wc | cat > output.txt  パイプが2つの場合");
    {
		t_command *first_command = cmd_init_cmdinvo((const char**)ft_split("cat /etc/passwd", ' '));

		t_command *second_command = cmd_init_cmdinvo((const char**)ft_split("wc", ' '));

		t_command *third_command = cmd_init_cmdinvo((const char**)ft_split("cat", ' '));
		cmd_add_outredirect(third_command, "output.txt", 1, false);

		cmd_cmdinvo_add_pipcmd(&first_command, second_command);
		cmd_cmdinvo_add_pipcmd(&first_command, third_command);

		int status = cmd_exec_commands(first_command);
		CHECK_EQ(status, 0);
		CHECK(system("cat /etc/passwd | wc | cat > expected.txt ; diff --color -u expected.txt output.txt") == 0);
		cmd_free_cmdinvo(first_command);
		remove("output.txt");
    }

    TEST_SECTION("cat /etc/passwd > /dev/null | wc | cat > output.txt  パイプの最初のコマンドでリダイレクトがある");
    {
		t_command *first_command = cmd_init_cmdinvo((const char**)ft_split("cat /etc/passwd", ' '));
		cmd_add_outredirect(first_command, "/dev/null", 1, false);

		t_command *second_command = cmd_init_cmdinvo((const char**)ft_split("wc", ' '));

		t_command *third_command = cmd_init_cmdinvo((const char**)ft_split("cat", ' '));
		cmd_add_outredirect(third_command, "output.txt", 1, false);

		cmd_cmdinvo_add_pipcmd(&first_command, second_command);
		cmd_cmdinvo_add_pipcmd(&first_command, third_command);

		int status = cmd_exec_commands(first_command);
		CHECK_EQ(status, 0);
		CHECK(system("cat /etc/passwd > /dev/null | wc | cat > expected.txt ; diff --color -u expected.txt output.txt") == 0);
		cmd_free_cmdinvo(first_command);
		remove("output.txt");
    }

    TEST_SECTION("cat test.h | wc < test.c | cat > output.txt  パイプの真ん中のコマンドでリダイレクトがある");
    {
		t_command *first_command = cmd_init_cmdinvo((const char**)ft_split("cat test.h", ' '));

		t_command *second_command = cmd_init_cmdinvo((const char**)ft_split("wc", ' '));
		cmd_add_inredirect(second_command, "test.c", 0);

		t_command *third_command = cmd_init_cmdinvo((const char**)ft_split("cat", ' '));
		cmd_add_outredirect(third_command, "output.txt", 1, false);

		cmd_cmdinvo_add_pipcmd(&first_command, second_command);
		cmd_cmdinvo_add_pipcmd(&first_command, third_command);

		int status = cmd_exec_commands(first_command);
		CHECK_EQ(status, 0);
		CHECK(system("cat test.h | wc < test.c | cat > expected.txt ; diff --color -u expected.txt output.txt") == 0);
		cmd_free_cmdinvo(first_command);
		remove("output.txt");
    }

    TEST_SECTION("存在するコマンドを実行すると返り値は0になる");
    {
		t_command *command = cmd_init_cmdinvo((const char**)ft_split("echo", ' '));

		int status = cmd_exec_commands(command);
		CHECK(status == 0);
		cmd_free_cmdinvo(command);
    }

    TEST_SECTION("存在しないコマンドを実行すると返り値は0以外になる");
    {
		remove("not_exists");
		t_command *command = cmd_init_cmdinvo((const char**)ft_split("not_exists", ' '));

		int status = cmd_exec_commands(command);
		CHECK(status != 0);
		cmd_free_cmdinvo(command);
    }

    TEST_SECTION("存在しないコマンドを実行してもリダイレクト先のファイルは作成される");
    {
		remove("not_exists");
		t_command *command = cmd_init_cmdinvo((const char**)ft_split("not_exists", ' '));
		cmd_add_outredirect(command, "output.txt", 1, false);

		remove("output.txt");
		int status = cmd_exec_commands(command);
		CHECK(status != 0);
		CHECK(system("ls -l output.txt") == 0);
		cmd_free_cmdinvo(command);
		remove("output.txt");
    }

	free_vars(g_shell.env);
	int fail_count = print_result();
	return (fail_count);
}
