#include <stdio.h>
#include <glib.h>

static guint counter = 0;

static void process_list_item(gpointer data, gpointer user_data)
{
    GSList *list = user_data;
    printf("g_slist_length(list)=%d, index=%d, data=%s\n", g_slist_length(list), counter++, data);
}

static void list_example()
{
    GSList *list = NULL;
    printf("g_slist_length(list)=%d\n", g_slist_length(list));
    list = g_slist_append(list, "apple");
    list = g_slist_append(list, "orange");
    list = g_slist_append(list, "pear");
    list = g_slist_append(list, "grape");
    printf("g_slist_length(list)=%d\n", g_slist_length(list));
    g_slist_foreach(list, process_list_item, list);
    g_slist_free(list);
}

static void hash_table_example()
{
    GHashTable *table = g_hash_table_new(g_str_hash, g_str_equal);
    g_hash_table_replace(table, g_strdup("first"), g_strdup("john"));
    g_hash_table_replace(table, g_strdup("last"), g_strdup("doe"));
    const gchar *first = g_hash_table_lookup(table, g_strdup("first"));
    const gchar *last = g_hash_table_lookup(table, g_strdup("last"));
    printf("first=%s, last=%s\n", first, last);
}

static void list_files(const gchar *parent)
{
    GDir *dir;
    const gchar *name;

    dir = g_dir_open(parent, 0, NULL);
    if (!dir)
        return;

    name = g_dir_read_name(dir);
    while (name != NULL)
    {
        gchar *path, *display_name;
        gboolean is_dir;

        if (name[0] != '.')
        {
            path = g_build_filename(parent, name, NULL);
            is_dir = g_file_test(path, G_FILE_TEST_IS_DIR);
            display_name = g_filename_to_utf8(name, -1, NULL, NULL, NULL);
            printf("%s\n", path);
            g_free(path);
            g_free(display_name);
        }

        name = g_dir_read_name(dir);
    }
    g_dir_close(dir);
}

static void list_directory_files_example()
{
    list_files(g_get_current_dir());
}

static void spawn_command_line_process_example()
{
    gchar *stdout, *stderr;
    gint *exit_status;
    GError *err;
    g_spawn_command_line_sync("ls", &stdout, &stderr, exit_status, &err);
    printf("stdout=%s\n", stdout);
    printf("stderr=%s\n", stderr);
}

int main(int argc, char **argv)
{
    list_example();
    hash_table_example();
    list_directory_files_example();
    spawn_command_line_process_example();

    return 0;
}
