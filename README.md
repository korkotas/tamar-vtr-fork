# Verilog to Routing (VTR)
[![Gitpod Ready-to-Code](https://img.shields.io/badge/Gitpod-Ready--to--Code-blue?logo=gitpod)](https://gitpod.io/#https://github.com/verilog-to-routing/vtr-verilog-to-routing.git)
[![Build Status](https://github.com/verilog-to-routing/vtr-verilog-to-routing/workflows/Test/badge.svg)](https://github.com/verilog-to-routing/vtr-verilog-to-routing/actions?query=workflow%3ATest) [![Documentation Status](https://readthedocs.org/projects/vtr/badge/?version=latest)](http://docs.verilogtorouting.org/en/latest/)

## Introduction
The Verilog-to-Routing (VTR) project is a world-wide collaborative effort to provide an open-source framework for conducting FPGA architecture and CAD research and development.
The VTR design flow takes as input a Verilog description of a digital circuit, and a description of the target FPGA architecture.
It then performs:
  * Elaboration, Synthesis & Partial Mapping (PARMYS)
  * Logic Optimization & Technology Mapping (ABC)
  * Packing, Placement, Routing & Timing Analysis (VPR)

to generate FPGA speed and area results.
VTR includes a set of benchmark designs known to work with the design flow.

VTR can also produce [FASM](https://fasm.readthedocs.io/en/latest/) to program some commercial FPGAs (via [Symbiflow](https://chipsalliance.org/announcement/2022/02/18/chips-alliance-forms-f4pga-workgroup-to-accelerate-adoption-of-open-source-fpga-tooling/))

| Placement (carry-chains highlighted) | Critical Path |
| ------------------------------------ | ------------- |
| <img src="https://verilogtorouting.org/img/des90_placement_macros.gif" width="350"/> | <img src="https://verilogtorouting.org/img/des90_cpd.gif" width="350"/> |

| Logical Connections | Routing Utilziation |
| ------------------- | ------------------- |
| <img src="https://verilogtorouting.org/img/des90_nets.gif" width="350"/> | <img src="https://verilogtorouting.org/img/des90_routing_util.gif" width="350"/> |


## Documentation
VTR's [full documentation](https://docs.verilogtorouting.org) includes tutorials, descriptions of the VTR design flow, and tool options.

Also check out our [additional support resources](SUPPORT.md).

## License
Generally most code is under MIT license, with the exception of ABC which is distributed under its own (permissive) terms.
See the [full license](LICENSE.md) for details.

## How to Cite
The following paper may be used as a general citation for VTR:

K. E. Murray, O. Petelin, S. Zhong, J. M. Wang, M. ElDafrawy, J.-P. Legault, E. Sha, A. G. Graham, J. Wu, M. J. P. Walker, H. Zeng, P. Patros, J. Luu, K. B. Kent and V. Betz "VTR 8: High Performance CAD and Customizable FPGA Architecture Modelling", ACM TRETS, 2020.

Bibtex:
```
@article{vtr8,
  title={VTR 8: High Performance CAD and Customizable FPGA Architecture Modelling},
  author={Murray, Kevin E. and Petelin, Oleg and Zhong, Sheng and Wang, Jai Min and ElDafrawy, Mohamed and Legault, Jean-Philippe and Sha, Eugene and Graham, Aaron G. and Wu, Jean and Walker, Matthew J. P. and Zeng, Hanqing and Patros, Panagiotis and Luu, Jason and Kent, Kenneth B. and Betz, Vaughn},
  journal={ACM Trans. Reconfigurable Technol. Syst.},
  year={2020}
}
```

## Download
For most users of VTR (rather than active developers) you should download the [latest official VTR release](https://verilogtorouting.org/download), which has been fully regression tested.

## Building
On unix-like systems run `make` from the root VTR directory.

For more details see the [building instructions](BUILDING.md).

#### Docker
We provide a Dockerfile that sets up all the necessary packages for VTR to run.
For more details see [here](dev/DOCKER_DEPLOY.md).

## Mailing Lists
If you have questions, or want to keep up-to-date with VTR, consider joining our mailing lists:

[VTR-Announce](https://groups.google.com/forum/#!forum/vtr-announce): VTR release announcements (low traffic)

[VTR-Users](https://groups.google.com/forum/#!forum/vtr-users): Discussions about using VTR

[VTR-Devel](https://groups.google.com/forum/#!forum/vtr-devel): Discussions about VTR development

[VTR-Commits](https://groups.google.com/forum/#!forum/vtr-commits): VTR revision control commits

## Development
This is the development trunk for the Verilog-to-Routing project.
Unlike the nicely packaged releases that we create, you are working with code in a constant state of flux.
You should expect that the tools are not always stable and that more work is needed to get the flow to run.

For new developers, please follow the [quickstart guide](https://docs.verilogtorouting.org/en/latest/quickstart/).

We follow a feature branch flow, where you create a new branch for new code, test it, measure its Quality of Results, and eventually produce a pull request for review by other developers. Pull requests that meet all the quality and review criteria are then merged into the master branch by a developer with the authority to do so.

In addition to measuring QoR and functionality automatically on pull requests, we do periodic automated testing of the master using BuildBot, and the results can be viewed below to track QoR and stability.
* [Trunk Status](http://builds.verilogtorouting.org:8080/waterfall)
* [QoR Tracking](http://builds.verilogtorouting.org:8080/)

*IMPORTANT*: A broken build must be fixed at top priority. You break the build if your commit breaks any of the automated regression tests.

For additional information see the [developer README](README.developers.md).

### Contributing to VTR
If you'd like to contribute to VTR see our [Contribution Guidelines](CONTRIBUTING.md).

## Contributors
*Please keep this up-to-date*

Professors: Kenneth Kent, Vaughn Betz, Jonathan Rose, Jason Anderson, Peter Jamieson

Research Assistants: Aaron Graham


Graduate Students: Kevin Murray, Jason Luu, Oleg Petelin, Xifian Tang, Mohamed Elgammal, Mohamed Eldafrawy, Jeffrey Goeders, Chi Wai Yu, Andrew Somerville, Ian Kuon, Alexander Marquardt, Andy Ye, Wei Mark Fang, Tim Liu, Charles Chiasson, Panagiotis (Panos) Patros, Jean-Philippe Legault, Aaron Graham, Nasrin Eshraghi Ivari, Maria Patrou, Scott Young, Sarah Khalid, Seyed Alireza Damghani, Harpreet Kaur, Daniel Khadivi, Alireza Azadi


Summer Students: Opal Densmore, Ted Campbell, Cong Wang, Peter Milankov, Scott Whitty, Michael Wainberg, Suya Liu, Miad Nasr, Nooruddin Ahmed, Thien Yu, Long Yu Wang, Matthew J.P. Walker, Amer Hesson, Sheng Zhong, Hanqing Zeng, Vidya Sankaranarayanan, Jia Min Wang, Eugene Sha, Jean-Philippe Legault, Richard Ren, Dingyu Yang, Alexandrea Demmings, Hillary Soontiens, Julie Brown, Bill Hu, David Baines, Mahshad Farahani, Helen Dai, Daniel Zhai

Companies: Intel, Huawei, Lattice, Altera Corporation, Texas Instruments, Google, Antmicro

Funding Agencies: NSERC, Semiconductor Research Corporation

# Tamar Korkotashvili 24



## Getting started

To make it easy for you to get started with GitLab, here's a list of recommended next steps.

Already a pro? Just edit this README.md and make it your own. Want to make it easy? [Use the template at the bottom](#editing-this-readme)!

## Add your files

- [ ] [Create](https://docs.gitlab.com/ee/user/project/repository/web_editor.html#create-a-file) or [upload](https://docs.gitlab.com/ee/user/project/repository/web_editor.html#upload-a-file) files
- [ ] [Add files using the command line](https://docs.gitlab.com/ee/gitlab-basics/add-file.html#add-a-file-using-the-command-line) or push an existing Git repository with the following command:

```
cd existing_repo
git remote add origin https://gitlab.epfl.ch/summer-at-epfl/tamar-24.git
git branch -M main
git push -uf origin main
```

## Integrate with your tools

- [ ] [Set up project integrations](https://gitlab.epfl.ch/summer-at-epfl/tamar-24/-/settings/integrations)

## Collaborate with your team

- [ ] [Invite team members and collaborators](https://docs.gitlab.com/ee/user/project/members/)
- [ ] [Create a new merge request](https://docs.gitlab.com/ee/user/project/merge_requests/creating_merge_requests.html)
- [ ] [Automatically close issues from merge requests](https://docs.gitlab.com/ee/user/project/issues/managing_issues.html#closing-issues-automatically)
- [ ] [Enable merge request approvals](https://docs.gitlab.com/ee/user/project/merge_requests/approvals/)
- [ ] [Set auto-merge](https://docs.gitlab.com/ee/user/project/merge_requests/merge_when_pipeline_succeeds.html)

## Test and Deploy

Use the built-in continuous integration in GitLab.

- [ ] [Get started with GitLab CI/CD](https://docs.gitlab.com/ee/ci/quick_start/index.html)
- [ ] [Analyze your code for known vulnerabilities with Static Application Security Testing (SAST)](https://docs.gitlab.com/ee/user/application_security/sast/)
- [ ] [Deploy to Kubernetes, Amazon EC2, or Amazon ECS using Auto Deploy](https://docs.gitlab.com/ee/topics/autodevops/requirements.html)
- [ ] [Use pull-based deployments for improved Kubernetes management](https://docs.gitlab.com/ee/user/clusters/agent/)
- [ ] [Set up protected environments](https://docs.gitlab.com/ee/ci/environments/protected_environments.html)

***

# Editing this README

When you're ready to make this README your own, just edit this file and use the handy template below (or feel free to structure it however you want - this is just a starting point!). Thanks to [makeareadme.com](https://www.makeareadme.com/) for this template.

## Suggestions for a good README

Every project is different, so consider which of these sections apply to yours. The sections used in the template are suggestions for most open source projects. Also keep in mind that while a README can be too long and detailed, too long is better than too short. If you think your README is too long, consider utilizing another form of documentation rather than cutting out information.

## Name
Choose a self-explaining name for your project.

## Description
Let people know what your project can do specifically. Provide context and add a link to any reference visitors might be unfamiliar with. A list of Features or a Background subsection can also be added here. If there are alternatives to your project, this is a good place to list differentiating factors.

## Badges
On some READMEs, you may see small images that convey metadata, such as whether or not all the tests are passing for the project. You can use Shields to add some to your README. Many services also have instructions for adding a badge.

## Visuals
Depending on what you are making, it can be a good idea to include screenshots or even a video (you'll frequently see GIFs rather than actual videos). Tools like ttygif can help, but check out Asciinema for a more sophisticated method.

## Installation
Within a particular ecosystem, there may be a common way of installing things, such as using Yarn, NuGet, or Homebrew. However, consider the possibility that whoever is reading your README is a novice and would like more guidance. Listing specific steps helps remove ambiguity and gets people to using your project as quickly as possible. If it only runs in a specific context like a particular programming language version or operating system or has dependencies that have to be installed manually, also add a Requirements subsection.

## Usage
Use examples liberally, and show the expected output if you can. It's helpful to have inline the smallest example of usage that you can demonstrate, while providing links to more sophisticated examples if they are too long to reasonably include in the README.

## Support
Tell people where they can go to for help. It can be any combination of an issue tracker, a chat room, an email address, etc.

## Roadmap
If you have ideas for releases in the future, it is a good idea to list them in the README.

## Contributing
State if you are open to contributions and what your requirements are for accepting them.

For people who want to make changes to your project, it's helpful to have some documentation on how to get started. Perhaps there is a script that they should run or some environment variables that they need to set. Make these steps explicit. These instructions could also be useful to your future self.

You can also document commands to lint the code or run tests. These steps help to ensure high code quality and reduce the likelihood that the changes inadvertently break something. Having instructions for running tests is especially helpful if it requires external setup, such as starting a Selenium server for testing in a browser.

## Authors and acknowledgment
Show your appreciation to those who have contributed to the project.

## License
For open source projects, say how it is licensed.

## Project status
If you have run out of energy or time for your project, put a note at the top of the README saying that development has slowed down or stopped completely. Someone may choose to fork your project or volunteer to step in as a maintainer or owner, allowing your project to keep going. You can also make an explicit request for maintainers.



