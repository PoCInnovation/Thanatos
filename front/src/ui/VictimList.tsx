import * as React from "react";
import { List, Datagrid, TextField, EmailField, UrlField } from 'react-admin';

export const VictimList = () => (
    <List>
        <Datagrid rowClick="edit">
            <TextField source="id" />
            <TextField source="hwid" />
            <TextField source="username" />
            <UrlField source="ip" />
            <TextField source="files" />
        </Datagrid>
    </List>
);
