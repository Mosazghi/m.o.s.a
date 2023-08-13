import {
  Body,
  Controller,
  Get,
  Post,
  Res,
  Session,
  UseGuards,
} from '@nestjs/common';
import * as mqtt from 'mqtt';
import { AuthenticatedGuard } from 'src/auth/authenticated.guard';
import { UserService } from 'src/user/user.service';
import { ShoplistService } from './shoplist.service';
@Controller('dashboard')
export class ShoplistController {
  private mqttClient: mqtt.MqttClient;

  constructor(
    private readonly shoplistService: ShoplistService,
    private readonly userService: UserService,
  ) {
    this.mqttClient = mqtt.connect('mqtt://10.0.0.13:1884'); // Replace with your broker URL
  }

  @UseGuards(AuthenticatedGuard)
  @Post('api/bestill')
  async logg(@Body() shoplist, @Session() bruker, @Res() res) {
    const dropSted = shoplist[0];
    const [komponenter] = shoplist.slice(1);

    if (komponenter.length > 0) {
      const user = await this.userService.findById(bruker.passport.user);

      const shoplistOrder = {
        dropSted: dropSted,
        komponenter: komponenter,
      };

      // Publiser shoplisten til MQTT brokeren.
      this.mqttClient.publish('shoplist', JSON.stringify(shoplistOrder));

      res.send({ user, dropSted, komponenter });

      return await this.shoplistService.bestillKomponenter(
        user.username,
        dropSted,
        komponenter,
      );
    } else {
      res.json({ error: 'Du har ikke valgt noen komponenter å bestille' });
      return null;
    }
  }

  @Get('api/bestilling')
  async getBestilling() {
    const bestilling = this.shoplistService.getBestilling();
    return bestilling;
  }
}
