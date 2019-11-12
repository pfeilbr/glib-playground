#include <stdio.h>
#include <glib.h>

static guint counter = 0;

void process(gpointer data, gpointer user_data)
{
    GSList *list = user_data;
    printf("g_slist_length(list)=%d, index=%d, data=%s\n", g_slist_length(list), counter++, data);
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

int main(int argc, char **argv)
{
    GSList *list = NULL;
    printf("g_slist_length(list)=%d\n", g_slist_length(list));
    list = g_slist_append(list, "apple");
    list = g_slist_append(list, "orange");
    list = g_slist_append(list, "pear");
    list = g_slist_append(list, "grape");
    printf("g_slist_length(list)=%d\n", g_slist_length(list));
    g_slist_foreach(list, process, list);
    g_slist_free(list);

    GHashTable *table = g_hash_table_new(g_str_hash, g_str_equal);
    g_hash_table_replace(table, g_strdup("first"), g_strdup("john"));
    g_hash_table_replace(table, g_strdup("last"), g_strdup("doe"));

    const gchar *first = g_hash_table_lookup(table, g_strdup("first"));
    const gchar *last = g_hash_table_lookup(table, g_strdup("last"));
    printf("first=%s, last=%s\n", first, last);

    list_files("/tmp");

    return 0;
}
