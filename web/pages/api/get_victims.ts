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
  fs.readdir(process.env.VICTIMS_PATH, (_, files) => {
    const victims: Victim[] = files.map(file => {
      const file_split = file.split("-");
      return {
        username: file_split[0],
        hwid: file_split[1]
      }
    })
    res.status(200).json({ victims: victims })
  });
}
