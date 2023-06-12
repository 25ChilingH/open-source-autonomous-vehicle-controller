import { defineConfig } from 'vitepress'


export default defineConfig({
  title: "OSAVC",
  base: '/open-source-autonomous-vehicle-controller/',
  themeConfig: {

    logo: '',

    search: {
      provider: 'local'
    },

    footer: {
      message: 'Footer Here',
      copyright: 'Copyright © copyright'
    },

    nav: [
      { text: 'Home', link: '/' },
      { text: 'About', link: '/about/' },
      { text: 'Contacts', link: '/contacts' },
    ],

    sidebar: [
      {
        text: 'Get Started',
        items: [
          { text: 'Introduction', link: '/introduction' },
          {
            text: 'What You Need',
            items: [
              { text: 'Hardware', link: '/hardware' },
              { text: 'Software', link: '/software' },
            ],
          },
          {
            text: 'Installations',
            items: [
              { text: 'Windows', link: '/windows' },
              { text: 'Linux/Mac OS', link: '/linux' },
            ],
          },
          { text: 'Build your First Project', link: '/project' },
        ],
      },
      {
        text: 'About',
        items: [
          { text: 'about', link: '/about/' },
          { text: 'Team', link: '/about/team.md' },
        ],
      },
      {
        text: 'References',
        items: [
          { text: 'api', link: '/api-examples' },
          { text: 'markdown', link: '/markdown-examples' },
        ],
      }
    ],

    socialLinks: [
      { icon: 'github', link: 'https://github.com/uccross/open-source-autonomous-vehicle-controller' },
    ]
  }
})
