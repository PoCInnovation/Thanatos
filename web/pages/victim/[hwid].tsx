import { Button, Card, Group, Modal, SimpleGrid, Text } from "@mantine/core";
import { NextPage } from "next";
import { useRouter } from "next/router";
import { useEffect, useState } from "react";

interface FileInfo {
  name: string
  info: any
}

interface Show {
  name: string
  content: any
}

const VictimPage: NextPage = () => {
  const router = useRouter();
  const { hwid } = router.query;
  const [filesInfos, setFilesInfos] = useState([]);
  const [showFile, setShowFile] = useState<Show>();
  const filesCard = filesInfos.map((fileInfo: FileInfo, index) =>
    <Card key="head" withBorder m="md" p="lg">
      <Card.Section pb="md" style={{ lineHeight: 1, display: 'block', justifyContent: 'center' }}>
        {/* <Group spacing={30} position="center"> */}
        <Group position="center">
          <Text size="lg">File name:</Text>
          <Text weight={500} color="blue" size="md">{fileInfo.name}</Text>
        </Group>
        <Group position="center">
          <Text size="lg">Size:</Text>
          {/* </Group> */}
          {/* <Group spacing = {30} position="center"> */}
          <Text color="blue" size="md">{fileInfo.info.size} bytes</Text>
        </Group>
        {/* </Group> */}
      </Card.Section>
      <Card.Section withBorder p="xs">
        <Group position="center">
          <Button onClick={() => {
            fetch(`/api/get_file_content?hwid=${hwid}&file_name=${fileInfo.name}`)
              .then(res => {
                return res.json()
              }).then(data => {
                console.log(data);
                setShowFile({
                  name: fileInfo.name,
                  content: data.file_content
                });
              })
          }}>
            Afficher le contenu
          </Button>
        </Group>
      </Card.Section>
    </Card>
  );

  useEffect(() => {
    if (router.isReady) {
      fetch(`/api/get_victim_files?hwid=${hwid}`)
        .then(res => {
          return res.json()
        }).then(data => {
          console.log(data.files_infos);
          setFilesInfos(data.files_infos);
        })
    }
  }, [router.isReady])

  return (
    <div>
      {showFile &&
        <Modal
          title={showFile.name}
          opened={showFile != null}
          onClose={() => { setShowFile(undefined) }}
          size="55%"
        >
          <Text style={{ whiteSpace: "pre-line" }}>{showFile.content}</Text>
        </Modal>
      }
      <SimpleGrid cols={6}>
        {filesCard}
      </SimpleGrid>
    </div>
  )
}

export default VictimPage;
