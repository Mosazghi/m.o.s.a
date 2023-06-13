import { Controller, Get, Post, Body } from '@nestjs/common';
import { KoordinaterService } from '../services/koordinater.service';
import { SendKoordinaterDto } from '../dto/SendKoordinaterDto';

@Controller('koordinater')
export class KoordinaterController {
  constructor(private readonly koordinaterService: KoordinaterService) {}

  @Get()
  async getSisteKoordinater() {
    const koordinat = this.koordinaterService.getSisteKoordinat();
    return koordinat;
  }

  @Post()
  sendKoordinater(@Body() koordinat: SendKoordinaterDto) {
    this.koordinaterService.postKoordinat(koordinat);
  }
}
