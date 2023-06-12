// See LICENSE.SiFive for license details.
// See LICENSE.Berkeley for license details.

package freechips.rocketchip.system

import org.chipsalliance.cde.config._
import freechips.rocketchip.subsystem._

import freechips.rocketchip.devices.tilelink.{BootROMLocated}

class WithCustomBootVector extends Config((site, here, up) => {
  case BootROMLocated(x) => up(BootROMLocated(x), site).map { p =>
    p.copy(hang = 0x10000, contentFileName = "./bootrom/bootrom.img")
  }
})

class CustomConfig extends Config(
    new WithCustomBootVector ++
    new WithNBigCores(1) ++
    new WithCoherentBusTopology ++
    new BaseConfig
)
