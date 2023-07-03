import { Injectable } from '@nestjs/common';
import { InjectModel } from '@nestjs/mongoose';
import { Model } from 'mongoose';
import { Shoplist } from './schema/shoplist.schema';
import { ShoplistType } from './type/shoplist.type';

@Injectable()
export class ShoplistService {
  constructor(
    @InjectModel(Shoplist.name) private readonly shoplistModel: Model<Shoplist>,
  ) {}

  async bestillKomponenter(
    bruker: string,
    dropSted: number,
    komponenter: ShoplistType[],
  ) {
    const bestillingInfo = { bruker, dropSted, komponenter };
    const bestill = new this.shoplistModel(bestillingInfo);
    console.log('BESTILL, SAVE:', bestill);
    await bestill.save();
    return bestill;
  }

  async getBestilling() {
    const bestilling = await this.shoplistModel
      .findOne()
      .sort({ _id: -1 })
      .exec();
    console.log('BESTILL, GET:', bestilling);
    return bestilling;
  }
}
