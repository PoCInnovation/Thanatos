import React from 'react';
import '../App.css';
import { Admin, Resource } from 'react-admin';
import { VictimList } from './VictimList'
import jsonServerProvider from 'ra-data-json-server';

const dataProvider = jsonServerProvider('https://jsonplaceholder.typicode.com');

function App() {
  return (
      <Admin dataProvider={dataProvider}>
        <Resource name="users" list={VictimList} />
      </Admin>
  );
}

export default App;
