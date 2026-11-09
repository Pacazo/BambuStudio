# BambuStudio, customised for the H2C

This is a personal fork of [Bambu Studio](https://github.com/bambulab/BambuStudio), the slicer for Bambu Lab 3D printers. It follows the upstream `master` branch and adds my own changes on top, in the `custom` branch.

## Why this fork exists

I print on a Bambu Lab H2C from Linux, on a LAN, and buy filament from the Japanese Bambu Lab store. Stock Bambu Studio got in the way often enough that I started fixing it: options the slicer engine supports but the UI does not show, dialogs that interrupt every slice, a filament inventory that needs a cloud account, a printer that vanishes from the device list when the network changes, and a number of GTK bugs. The changes are made for my own setup and are tested only on the H2C and on Linux.

## What it improves over the original

Everything this fork adds or changes is marked in the UI with a red ●, so it is easy to tell apart from stock Bambu Studio. Advanced and developer mode parameters get a green and a dark green ● too. The marks can be hidden in Preferences.

**Slicing and print quality**
- Override the chamber and bed temperatures for the whole print from the process settings, with an option to keep the chamber closed instead of cooled.
- Ironing flow calibration test in the Calibration menu: one band ironed with the flow growing from a minimum to a maximum, labelled with the filament name and colour code.
- "Minimum line width on interface", for the layer resting directly on supports or on a raft.
- "Raft expansion" shown in the UI, and honoured by the tree support generator.
- Speeds set on an object or a height range apply to every nozzle, not only to the left one.
- No more oozing travel across the sparse bands of the prime tower.
- Process defaults tuned for the H2C: Arachne walls, no arc fitting, support ironing on.

**Workflow**
- "Filament grouping mode": choose once how filaments are assigned to the nozzles instead of answering the dialog before every slice.
- "Start delay" when sending a print job: the printer waits the given minutes before starting.
- Offline Filament Manager: the spool inventory is kept in a local file, with no cloud account and nothing sent to Bambu Lab.
- LAN printers stay in the device list when they are offline or the network changes, reconnect on their own, and can follow a change of subnet. Only the remove button forgets a printer.
- The left/right nozzle switches are hidden on printers whose two nozzles are alike (H2C, H2D).
- Filament prices in JPY, from the Japanese store.

**Interface**
- F1 to F12 select the main tabs, and Tab moves between fields with a visible focus indicator on GTK.
- Filament names next to the colour swatches in the object list.
- Tooltips and popups close when the application loses the focus.
- Tooltips for the many options that had none.
- Assorted fixes: crashes when starting a second instance and when slicing some 3mf files, the printing progress label, the object list context menu on GTK.

The version string carries a custom suffix, so a build of this fork is never mistaken for an official release. There are no prebuilt binaries: build it following the Linux guide below.

The original README follows.

---

![image](https://user-images.githubusercontent.com/106916061/179006347-497d24c0-9bd6-45b7-8c49-d5cc8ecfe5d7.png)
# BambuStudio
Bambu Studio is a cutting-edge, feature-rich slicing software.  
It contains project-based workflows, systematically optimized slicing algorithms, and an easy-to-use graphic interface, bringing users an incredibly smooth printing experience.

Prebuilt Windows, macOS 64-bit and Linux releases are available through the [github releases page](https://github.com/bambulab/BambuStudio/releases/).

Bambu Studio is based on [PrusaSlicer](https://github.com/prusa3d/PrusaSlicer) by Prusa Research, which is from [Slic3r](https://github.com/Slic3r/Slic3r) by Alessandro Ranellucci and the RepRap community.

See the [wiki](https://github.com/bambulab/BambuStudio/wiki) and the [documentation directory](https://github.com/bambulab/BambuStudio/tree/master/doc) for more information.

# What are Bambu Studio's main features?
Key features are:
- Basic slicing features & GCode viewer
- Multiple plates management
- Remote control & monitoring
- Auto-arrange objects
- Auto-orient objects
- Hybrid/Tree/Normal support types, Customized support
- multi-material printing and rich painting tools
- multi-platform (Win/Mac/Linux) support
- Global/Object/Part level slicing parameters

Other major features are:
- Advanced cooling logic controlling fan speed and dynamic print speed
- Auto brim according to mechanical analysis
- Support arc path(G2/G3)
- Support STEP format
- Assembly & explosion view
- Flushing transition-filament into infill/object during filament change

# How to compile
Following platforms are currently supported to compile:
- Windows 64-bit, [Compile Guide](https://github.com/bambulab/BambuStudio/wiki/Windows-Compile-Guide)
- Mac 64-bit, [Compile Guide](https://github.com/bambulab/BambuStudio/wiki/Mac-Compile-Guide)
- Linux, [Compile Guide](https://github.com/bambulab/BambuStudio/wiki/Linux-Compile-Guide)
  - currently we only provide linux appimages on [github releases](https://github.com/bambulab/BambuStudio/releases) for Ubuntu/Fedora, and a [flathub version](https://flathub.org/apps/com.bambulab.BambuStudio) can be used for all the linux platforms

# Report issue
You can add an issue to the [github tracker](https://github.com/bambulab/BambuStudio/issues) if **it isn't already present.**

# License
Bambu Studio is licensed under the GNU Affero General Public License, version 3. Bambu Studio is based on PrusaSlicer by PrusaResearch.

PrusaSlicer is licensed under the GNU Affero General Public License, version 3. PrusaSlicer is owned by Prusa Research. PrusaSlicer is originally based on Slic3r by Alessandro Ranellucci.

Slic3r is licensed under the GNU Affero General Public License, version 3. Slic3r was created by Alessandro Ranellucci with the help of many other contributors.

The GNU Affero General Public License, version 3 ensures that if you use any part of this software in any way (even behind a web server), your software must be released under the same license.

The bambu networking plugin is based on non-free libraries. It is optional to the Bambu Studio and provides extended networking functionalities for users.
By default, after installing Bambu Studio without the networking plugin, you can initiate printing through the SD card after slicing is completed.

